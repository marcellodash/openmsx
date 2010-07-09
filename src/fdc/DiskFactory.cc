// $Id$

#include "DiskFactory.hh"
#include "CommandController.hh"
#include "Reactor.hh"
#include "File.hh"
#include "DSKDiskImage.hh"
#include "XSADiskImage.hh"
#include "RamDSKDiskImage.hh"
#include "DirAsDSK.hh"
#include "DiskPartition.hh"
#include "GlobalSettings.hh"
#include "EnumSetting.hh"
#include "MSXException.hh"
#include "StringOp.hh"
#include "shared_ptr.hh"

using std::string;

namespace openmsx {

DiskFactory::DiskFactory(Reactor& reactor_)
	: reactor(reactor_)
{
	CommandController& controller = reactor.getCommandController();

	EnumSetting<DirAsDSK::SyncMode>::Map syncDirAsDSKMap;
	syncDirAsDSKMap["read_only"] = DirAsDSK::SYNC_READONLY;
	syncDirAsDSKMap["cached_write"] = DirAsDSK::SYNC_CACHEDWRITE;
	syncDirAsDSKMap["nodelete"] = DirAsDSK::SYNC_NODELETE;
	syncDirAsDSKMap["full"] = DirAsDSK::SYNC_FULL;
	syncDirAsDSKSetting.reset(new EnumSetting<DirAsDSK::SyncMode>(
		controller, "DirAsDSKmode",
		"type of syncronisation between host directory and dir-as-dsk diskimage",
		DirAsDSK::SYNC_FULL, syncDirAsDSKMap));

	EnumSetting<DirAsDSK::BootSectorType>::Map bootsectorMap;
	bootsectorMap["DOS1"] = DirAsDSK::BOOTSECTOR_DOS1;
	bootsectorMap["DOS2"] = DirAsDSK::BOOTSECTOR_DOS2;
	bootSectorSetting.reset(new EnumSetting<DirAsDSK::BootSectorType>(
		controller, "bootsector", "boot sector type for dir-as-dsk",
		DirAsDSK::BOOTSECTOR_DOS2, bootsectorMap));
}

Disk* DiskFactory::createDisk(const string& diskImage)
{
	CommandController& controller = reactor.getCommandController();

	if (diskImage == "ramdsk") {
		return new RamDSKDiskImage();
	}

	Filename filename(diskImage, controller);
	try {
		// First try DirAsDSK
		return new DirAsDSK(
			controller.getCliComm(),
			filename,
			syncDirAsDSKSetting->getValue(),
			bootSectorSetting->getValue());
	} catch (MSXException&) {
		// DirAsDSK didn't work, no problem
	}
	try {
		std::auto_ptr<File> file(new File(filename, File::PRE_CACHE));
		file->setFilePool(reactor.getFilePool());

		try {
			// first try XSA
			return new XSADiskImage(filename, *file);
		} catch (MSXException&) {
			// XSA didn't work, still no problem
		}
		// next try normal DSK
		return new DSKDiskImage(filename, file);

	} catch (MSXException& e) {
		// File could not be opened or (very rare) something is wrong
		// with the DSK image. Try to interpret the filename as
		//    <filename>:<partition-number>
		// Try this last because the ':' character could be
		// part of the filename itself. So only try this if
		// the name could not be interpreted as a valid
		// filename.
		string::size_type pos = diskImage.find_last_of(':');
		if (pos == string::npos) {
			// does not contain ':', throw previous exception
			throw;
		}
		shared_ptr<SectorAccessibleDisk> wholeDisk;
		try {
			Filename filename2(diskImage.substr(0, pos));
			wholeDisk.reset(new DSKDiskImage(filename2));
		} catch (MSXException&) {
			// If this fails we still prefer to show the
			// previous error message, because it's most
			// likely more descriptive.
			throw e;
		}
		unsigned num = StringOp::stringToUint(
			diskImage.substr(pos + 1));
		return new DiskPartition(*wholeDisk, num, wholeDisk);
	}
}

} // namespace openmsx
