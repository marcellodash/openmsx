// $Id$

#include <string>
#include "MSXRomDevice.hh"
#include "MSXDiskRomPatch.hh"
#include "MSXTapePatch.hh"
#include "MSXCPUInterface.hh"
#include "MSXRomPatchInterface.hh"
#include "File.hh"


MSXRomDevice::MSXRomDevice(MSXConfig::Device* config, const EmuTime &time)
{
	// open file
	file = new File(config->getParameter("filename"), ROM);
	
	// get filesize
	int fileSize;
	if (config->hasParameter("filesize") &&
	    config->getParameter("filesize") != "auto") {
		fileSize = config->getParameterAsInt("filesize");
	} else {
		fileSize = file->size();
	}
	
	// get offset
	int offset = 0;
	if (config->hasParameter("skip_headerbytes")) {
		offset = config->getParameterAsInt("skip_headerbytes");
	}

	// some checks 
	size = fileSize - offset;
	if (size <= 0) {
		PRT_ERROR("Offset greater than filesize");
	}
	
	// read file
	try {
		byte *tmp = file->mmap();
		rom = tmp + offset;
	} catch (FileException &e) {
		PRT_ERROR("Error reading ROM image: " << config->getParameter("filename"));
	}
	
	// for each patchcode parameter, construct apropriate patch
	// object and register it at MSXCPUInterface
	std::list<MSXConfig::Config::Parameter*>* parameters =
		config->getParametersWithClass("patchcode");
	std::list<MSXConfig::Config::Parameter*>::const_iterator it;
	for (it=parameters->begin(); it!=parameters->end(); it++) {
		MSXRomPatchInterface* patchInterface;
		if ((*it)->value == "MSXDiskRomPatch") {
			patchInterface = new MSXDiskRomPatch(time);
		} else if ((*it)->value == "MSXTapePatch") {
			patchInterface = new MSXTapePatch();
		} else {
			PRT_ERROR("Unknown patch interface");
		}
		romPatchInterfaces.push_back(patchInterface);
		MSXCPUInterface::instance()->registerInterface(patchInterface);
	}
	config->getParametersWithClassClean(parameters);
	
	// also patch the file if needed:
	std::list<MSXConfig::Config::Parameter*>* parameters2 =
		config->getParametersWithClass("patch");
	std::list<MSXConfig::Config::Parameter*>::const_iterator i;
	for (i=parameters2->begin(); i!=parameters2->end(); i++) {
		int offset = strtol((*i)->name.c_str(), 0, 0);
		int value  = (*i)->getAsInt();
		if (offset >= size) {
			PRT_DEBUG("Ignoring illegal ROM patch-offset: " << offset);
		} else {
			PRT_DEBUG("Patching ROM[" << (*i)->name << "]=" << (*i)->value);
			rom[offset] = value;
		}
	}
	config->getParametersWithClassClean(parameters2);
}


MSXRomDevice::~MSXRomDevice()
{
	std::list<MSXRomPatchInterface*>::iterator i;
	for (i=romPatchInterfaces.begin(); i!=romPatchInterfaces.end(); i++) {
		MSXCPUInterface::instance()->unregisterInterface(*i);
		delete (*i);
	}
	file->munmap();
	delete file;
}
