// $Id$

#ifndef __MSXROM_HH__
#define __MSXROM_HH__

#ifndef VERSION
#include "config.h"
#endif

#include "MSXRomDevice.hh"
#include "MSXMemDevice.hh"
#include "RomTypes.hh"
#include "CommandLineParser.hh"

// forward declarations
class SCC;
class DACSound;
class SRAM;


class MSXRomCLI : public CLIOption, public CLIFileType
{
	public:
		MSXRomCLI();
		virtual void parseOption(const std::string &option,
			std::list<std::string> &cmdLine);
		virtual const std::string& optionHelp();
		virtual void parseFileType(const std::string &filename);
		virtual const std::string& fileTypeHelp();
	
	private:
		int cartridgeNr;
};

class MSXRomCLIPost : public CLIPostConfig
{
	public:
		MSXRomCLIPost(const std::string &arg);
		virtual ~MSXRomCLIPost() {}
		virtual void execute(MSXConfig::Backend *config);
	protected:
		int ps, ss;
		const std::string arg;
};
class MSXRomPostName : public MSXRomCLIPost
{
	public:
		MSXRomPostName(int slot, const std::string &arg);
		virtual ~MSXRomPostName() {}
		virtual void execute(MSXConfig::Backend *config);
	private:
		int slot;
};
class MSXRomPostNoName : public MSXRomCLIPost
{
	public:
		MSXRomPostNoName(const std::string &arg);
		virtual ~MSXRomPostNoName() {}
		virtual void execute(MSXConfig::Backend *config);
};


class MSXRom : public MSXMemDevice
{
	public:
		MSXRom(MSXConfig::Device *config, const EmuTime &time);
		virtual ~MSXRom();

		virtual void reset(const EmuTime &time);
		virtual byte readMem(word address, const EmuTime &time);
		virtual void writeMem(word address, byte value, const EmuTime &time);
		virtual byte* getReadCacheLine(word start);
		
	private:
		void retrieveMapperType();
		bool mappedOdd();
		
		inline void setBank4kB (int region, byte* adr);
		inline void setBank8kB (int region, byte* adr);
		inline void setBank16kB(int region, byte* adr);
		inline void setROM4kB  (int region, int block);
		inline void setROM8kB  (int region, int block);
		inline void setROM16kB (int region, int block);
	
		MapperType mapperType;
		byte *internalMemoryBank[16];	// 16 blocks of 4kB
		byte *unmapped;
		
		MSXRomDevice rom;
		SRAM *sram;
		byte regioSRAM;	//bit n=1 => SRAM in [n*0x2000, (n+1)*0x2000)

		SCC* cartridgeSCC;
		bool enabledSCC;
		DACSound* dac;

		byte control;
		int bankSelect[8];
		int sramAddr;
};

#endif
