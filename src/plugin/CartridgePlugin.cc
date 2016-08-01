#include "CartridgePlugin.hh"

#include "MSXDevice.hh"
#include "MSXMotherBoard.hh"
#include "MSXCPUInterface.hh"
#include "MSXException.hh"
#include "MSXCPU.hh"
#include "CPURegs.hh"
#include "CommandController.hh"
#include "serialize.hh"
#include "HardwareConfig.hh"
#include "CacheLine.hh"
#include "CliComm.hh"
#include "FileOperations.hh"

#if defined(__linux__)
#include <dlfcn.h>
#endif

#include <codecvt>

using namespace std;

using namespace openmsx::FileOperations;

namespace openmsx {

typedef uint32_t(*tOpenMsxPluginEntry) (CartridgePluginInterface *, long major, long minor);

static class EvtDummy : public CartridgePluginEventInterface
{
public:
   void OnOpenMsxPowerUp(uint64_t /*time*/) override { };
   void OnOpenMsxPowerDown(uint64_t /*time*/) override {};
   void OnOpenMsxReset(uint64_t /*time*/) override {};
   void OnOpenMsxWriteMem(uint16_t /*address*/, uint8_t /*value*/, uint16_t /*pc*/, uint64_t /*time*/) override {};
   void OnOpenMsxGlobalInpRead(uint16_t /*address*/, uint8_t /*value*/, uint16_t /*pc*/, uint64_t /*time*/) override {};
   void OnOpenMsxGlobalOutpWrite(uint16_t /*address*/, uint8_t /*value*/ , uint16_t /*pc*/ , uint64_t /*time*/ ) override {};
   void OnOpenMsxGlobalRead(uint16_t /*address*/, uint8_t /*value*/, uint16_t /*pc*/ , uint64_t /*time*/ ) override {};
   void OnOpenMsxGlobalWrite(uint16_t /*address*/, uint8_t /*value*/, uint16_t /*pc*/, uint64_t /*time*/) override {};
   uint8_t *OnOpenMsxGetWriteCacheLine(uint16_t /*start*/) const override { return nullptr; };
   uint8_t OnOpenMsxPeekMem(uint16_t /*address*/) override { return 0; };
   const uint8_t* OnOpenMsxGetReadCacheLine(uint16_t /*start*/) const override { return nullptr; };
   uint8_t OnOpenMsxReadMem(uint16_t /*address*/, uint16_t /*pc*/, uint64_t /*time*/) override { return 0; };
   void OnOpenMsxWriteIO(uint16_t /*port*/, uint8_t /*value*/, uint16_t /*pc*/, uint16_t /*time*/) override {};
   uint8_t OnOpenMsxReadIO(uint16_t /*port*/, uint16_t /*pc*/, uint16_t /*time*/) override { return 0; };
   uint8_t OnOpenMsxPeekIO(uint16_t /*port*/) override { return 0; };
   void OnOpenMsxIorqM1(uint64_t /*time*/) override {};
   bool OnOpenMsxPluginLoad(void) override { return true; };
   bool OnOpenMsxPluginUnLoad(void) override  { return true; };
} evtdummy;

HMODULE CartridgePlugin::LoadPlugin(const string &filename)
{
#if defined(WINDOWS)
   // Get DLL name. Convert UTF8 to UTF16
   std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
   dllname = converter.from_bytes(filename);

	return LoadLibrary(dllname.c_str());
#else
   return dlopen(filename.c_str(), RTLD_LAZY);
#endif
}

CartridgePlugin::CartridgePlugin(const DeviceConfig& config) : MSXDevice(config), evt(&evtdummy)
{
   string reason;

   const XMLElement& dllConfig = config.getChild("dll");

   // DLL name plugin
   string dll = dllConfig.getChildData("filename");
   string file;

   file = dll;
   module = LoadPlugin(file);

   if(module == nullptr)
   {
      // Trys to load the DLL from user data directory
      file = getUserDataDir() + "/plugins/" + dll;
      module = LoadPlugin(file);
   }

   if(module == nullptr)
   {
      // Trys to load the DLL from system data directory
      file = getSystemDataDir() + "/plugins/" + dll;
      module = LoadPlugin(file);
   }

	if(module != nullptr)
	{
      pluginPrintInfo(string("Loaded from: ") + file);

		tOpenMsxPluginEntry entry;

		// Get the plugin entry point
#if defined(WINDOWS)
        entry = (tOpenMsxPluginEntry)GetProcAddress(module, "OpenMsxPluginEntry");
#else
        entry = (tOpenMsxPluginEntry)dlsym(module, "OpenMsxPluginEntry");
#endif

		if(entry)
		{
			// Execute DLL procedure
			int32_t ret = entry(this, MAJOR, MINOR);

			if(ret == 0)
			{
				// Signal plugin load
				if(!evt->OnOpenMsxPluginLoad())
					reason = "OnOpenMsxPluginLoad()";
			}
			else
			{
				reason = "OpenMsxPluginEntry() return code " + ret;
			}
		}
		else
			reason = "GetProcAddress()";
	}
	else
		reason = "LoadLibrary()";

	if(reason.size())
	{
		throw MSXException("Loading cartridge plugin \"" + 
							getName() +
			                "\" failed. Reason: " + reason);
	}
}

CartridgePlugin::~CartridgePlugin()
{
	// Signal plugin unload
	evt->OnOpenMsxPluginUnLoad();

	// Unload DLL plugin
#if defined(WINDOWS)
	FreeLibrary(module);
#else
   dlclose(module);
#endif
}

bool CartridgePlugin::pluginIsM1Cycle(uint16_t address)
{
   return this->getCPU().isM1Cycle(address);
}

/**
 * Executes a TCL command
 */
bool CartridgePlugin::pluginExecute(const char *cmd)
{
	getCommandController().executeCommand(cmd);

	return true;
}

/**
 * Get Z80 program counter (PC)
 */
uint16_t CartridgePlugin::pluginGetPC(void)
{
   return getCPU().getRegisters().getPC();
}

void CartridgePlugin::pluginGetConfigValue(const char *name, char *value, int size)
{
	if(value == nullptr || size <= 1)
		return;

	const XMLElement& dllConfig = getDeviceConfig().getChild("dll");
	string v = dllConfig.getChildData(name);

	// Copy value and truncate size
	std::memcpy(value, v.c_str(), std::min(int(v.size()), size - 1));
	value[std::min(int(v.size()), size - 1)] = 0;
}

void CartridgePlugin::pluginPrintWarning(const char *msg, ...)
{
	string m = "Plugin \"" + getName() + "\" | " + string(msg);
	getCliComm().printWarning(m);
}

void CartridgePlugin::pluginPrintError(const char *msg, ...)
{
	string m = "Plugin \"" + getName() + "\" | " + string(msg);
	getCliComm().printError(m);
}

void CartridgePlugin::pluginPrintProgress(const char *msg, ...)
{
	string m = "Plugin \"" + getName() + "\" | " + string(msg);
	getCliComm().printProgress(m);
}

void CartridgePlugin::pluginPrintInfo(const string &msg)
{
	string m = "Plugin \"" + getName() + "\" | " + msg;
	getCliComm().printInfo(m);
}

void CartridgePlugin::pluginPrintInfo(const char *msg, ...)
{
	string m = "Plugin \"" + getName() + "\" | " + string(msg);
	getCliComm().printInfo(m);
}

void CartridgePlugin::RegisterEvents(plugin::CartridgePluginEventInterface *evt_)
{
	if (evt_ == nullptr)
	{
		// Prevent null pointer exception by using a pointer to a dummy instance
		evt = &evtdummy;  
	}
	else
	{
		// Set event handler to the plugin interface 
		evt = evt_;
	}
}

void CartridgePlugin::pluginInvalidateMemCache(uint16_t start, unsigned size)
{
	invalidateMemCache(start, size);
}

/**
 * Plugin want reset the openmsx
 */
void CartridgePlugin::pluginReset(void)
{
	getCPU().doReset(EmuTime(0));
}

/**
 * Plugin wants power down openmsx
 */
void CartridgePlugin::pluginPowerDown(void)
{
	//getMotherBoard().powerDown();
}

/**
 * Plugin wants power up openmsx
 */
void CartridgePlugin::pluginPowerUp(void)
{
	//getMotherBoard().powerUp();
}

/**
 * Power up event generated on openmsx
 * Fire event on plugin
 */
void CartridgePlugin::powerUp(EmuTime::param time)
{
	evt->OnOpenMsxPowerUp(time.time);
}

/**
 * Power down event generated on openmsx
 * Fire event on plugin
 */
void CartridgePlugin::powerDown(EmuTime::param time)
{
	evt->OnOpenMsxPowerDown(time.time);
}

/**
 * Reset event generated on openMSX
 * Fire event on plugin
 */
void CartridgePlugin::reset(EmuTime::param time)
{
	evt->OnOpenMsxReset(time.time);
}

void CartridgePlugin::globalRead(word address, byte value, EmuTime::param time)
{
   evt->OnOpenMsxGlobalRead(address, value, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::globalReadOpcode(word address, byte value, unsigned /*pc*/, EmuTime::param time)
{
   evt->OnOpenMsxGlobalRead(address, value, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::globalWrite(word address, byte value, EmuTime::param time)
{
   evt->OnOpenMsxGlobalWrite(address, value, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::globalInRead(word port, byte value, EmuTime::param time)
{
   evt->OnOpenMsxGlobalInpRead(port, value, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::globalOutWrite(word port, byte value, EmuTime::param time)
{
   evt->OnOpenMsxGlobalOutpWrite(port, value, getCPUInterface().GetMarkedPc(), time.time);
}

byte CartridgePlugin::peekMem(word address, EmuTime::param /*time*/) const
{
   return evt->OnOpenMsxPeekMem(address);
}

void CartridgePlugin::pluginRegisterGlobalWrite(uint16_t address)
{
	getCPUInterface().registerGlobalWrite(*this, address);
}

void CartridgePlugin::pluginUnregisterGlobalWrite(uint16_t address)
{
	getCPUInterface().registerGlobalWrite(*this, address);
}

void CartridgePlugin::pluginRegisterGlobalRead(uint16_t mask, uint16_t address, uint32_t opcodes)
{
   getCPUInterface().registerGlobalRead(*this, mask, address, opcodes);
}

void CartridgePlugin::pluginUnregisterGlobalRead(uint16_t mask, uint16_t address)
{
   getCPUInterface().unregisterGlobalRead(*this, mask, address);
}

void CartridgePlugin::pluginRegisterIoGlobalRead(uint8_t port)
{
   getCPUInterface().registerIoGlobalRead(*this, port);
}

void CartridgePlugin::pluginUnregisterIoGlobalRead(uint8_t port)
{
   getCPUInterface().unregisterIoGlobalRead(*this, port);
}

void CartridgePlugin::pluginRegisterIoGlobalWrite(uint8_t port)
{
   getCPUInterface().registerIoGlobalWrite(*this, port);
}

void CartridgePlugin::pluginUnregisterIoGlobalWrite(uint8_t port)
{
   getCPUInterface().unregisterGlobalWrite(*this, port);
}

int CartridgePlugin::pluginGetCacheLineSize(void)
{
	return CacheLine::SIZE;
}

const byte* CartridgePlugin::getReadCacheLine(word start) const
{
	return evt->OnOpenMsxGetReadCacheLine(start);
}

byte CartridgePlugin::readMem(word address, EmuTime::param time)
{
   return evt->OnOpenMsxReadMem(address, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::writeMem(word address, byte value, EmuTime::param time)
{
   evt->OnOpenMsxWriteMem(address, value, getCPUInterface().GetMarkedPc(), time.time);
}

byte *CartridgePlugin::getWriteCacheLine(word start) const
{
   return evt->OnOpenMsxGetWriteCacheLine(start);
}

byte CartridgePlugin::readIO(word port, EmuTime::param time)
{
   return evt->OnOpenMsxReadIO(port, getCPUInterface().GetMarkedPc(), time.time);
}

byte CartridgePlugin::peekIO(word port, EmuTime::param /*time*/) const
{
	return evt->OnOpenMsxPeekIO(port);
}

void CartridgePlugin::writeIO(word port, byte value, EmuTime::param time)
{
   evt->OnOpenMsxWriteIO(port, value, getCPUInterface().GetMarkedPc(), time.time);
}

void CartridgePlugin::irqM1Cycle(EmuTime::param time)
{
   evt->OnOpenMsxIorqM1(time.time);
}

template<typename Archive>
void CartridgePlugin::serialize(Archive& ar, unsigned /*version*/)
{
	ar.template serializeBase<MSXDevice>(*this);
}

INSTANTIATE_SERIALIZE_METHODS(CartridgePlugin);
REGISTER_MSXDEVICE(CartridgePlugin, "Plugin");

} // namespace openmsx
