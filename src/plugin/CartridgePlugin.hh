#ifndef CARTRIDGEPLUGIN_HH
#define CARTRIDGEPLUGIN_HH

#include "MSXDevice.hh"
#include "CartridgePluginInterface.hh"

#include <memory>
#include <string>
#include <stdint.h>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#define WINDOWS
#elif defined(__linux__)
#define HMODULE void *
#else
#error Platform not supported
#endif

using namespace std;
using namespace plugin;

namespace openmsx {

class CartridgePlugin : public MSXDevice, public CartridgePluginInterface
{
public:
   void powerUp(EmuTime::param time) override;
   void powerDown(EmuTime::param time) override;
   void reset(EmuTime::param time) override;
   void irqM1Cycle(EmuTime::param time) override;

   byte peekMem(word address, EmuTime::param time) const override;
   byte readMem(word address, EmuTime::param time) override;
   void writeMem(word address, byte value, EmuTime::param time) override;

   byte readIO(word port, EmuTime::param time) override;
   void writeIO(word port, byte value, EmuTime::param time) override;
   byte peekIO(word port, EmuTime::param time) const override;

   void globalWrite(word address, byte value, EmuTime::param time) override;
   void globalRead(word address, byte value, EmuTime::param time) override;
   void globalReadOpcode(word address, byte value, unsigned pc, EmuTime::param time) override;
   void globalInRead(word port, byte value, EmuTime::param time) override;
   void globalOutWrite(word port, byte value, EmuTime::param time) override;
   byte* getWriteCacheLine(word start) const override;
   const byte* getReadCacheLine(word start) const override;

   void pluginRegisterGlobalRead(uint16_t mask, uint16_t address, uint32_t opcodes) override;
   void pluginUnregisterGlobalRead(uint16_t mask, uint16_t address) override;

   void pluginRegisterIoGlobalWrite(uint8_t port);
   void pluginUnregisterIoGlobalWrite(uint8_t port);

   void pluginRegisterIoGlobalRead(uint8_t port) override;
   void pluginUnregisterIoGlobalRead(uint8_t port) override;

   int pluginGetCacheLineSize(void) override;

   uint16_t pluginGetPC(void) override;

   explicit CartridgePlugin(const DeviceConfig& config);
   virtual ~CartridgePlugin();

   template<typename Archive>
   void serialize(Archive& ar, unsigned version);

protected:
   void RegisterEvents(CartridgePluginEventInterface *evt_) override;

   void pluginInvalidateMemCache(uint16_t start, unsigned size);
   void pluginPrintWarning(const char *msg, ...);
   void pluginPrintError(const char *msg, ...);
   void pluginPrintProgress(const char *msg, ...);
   void pluginPrintInfo(const char *msg, ...);
   void pluginPrintInfo(const string &msg);
   void pluginPowerUp(void) override;
   void pluginPowerDown(void) override;
   void pluginReset(void) override;
   bool pluginExecute(const char *) override;
   void pluginGetConfigValue(const char *name, char *value, int size) override;
   void pluginRegisterGlobalWrite(uint16_t address) override;
   void pluginUnregisterGlobalWrite(uint16_t address) override;
   bool pluginIsM1Cycle(uint16_t address) override;

private:
   wstring dllname;
   HMODULE module;

   HMODULE LoadPlugin(const string &filename);

   CartridgePluginEventInterface *evt;
};

} // namespace openmsx

#endif
