#include "nes.h"
#include "cpu_memory.h"

Nes::Nes()
{
	m_ram = std::make_shared<std::vector<uint8_t>>(ramSize);

	m_cpu = std::make_unique<LibMos6502::Mos6502>(std::make_shared<CpuMemory>(m_ram, m_cartridge.m_mapper));
}

void Nes::loadCartridge(std::istream& romStream)
{
	size_t size;
	char header[Cartridge::Rom::headerSize + 1];
	char temp;
	uint8_t mapperNumber;
	bool trainerPresent;
	Mapper::Mirroring mirroring;

	// Determine stream size
	romStream.seekg(0, std::ios_base::end);
	size = romStream.tellg();

	romStream.seekg(0, std::ios_base::beg);

	// Validate header
	romStream.read(header, Cartridge::Rom::headerSize);
	header[sizeof(header) - 1] = 0;
	if (std::strcmp(header, Cartridge::Rom::header) != 0)
	{
		// TODO: Handle invalid header.
		return;
	}

	// Determine prg & chr ROM size
	romStream.read(&temp, 1);
	m_cartridge.m_rom->m_prgRom.resize(temp * Cartridge::Rom::prgRomSizeMultiplier);
	romStream.read(&temp, 1);
	m_cartridge.m_rom->m_chrRom.resize(temp * Cartridge::Rom::chrRomSizeMultiplier);

	// Byte 6	NNNN FTBM
	//			|||| |||*- Mirroring (if not four screen)
	//			|||| ||*-- ?
	//			|||| |*--- Trainer present
	//			|||| *---- Four screen mirroring
	//			****------ Mapper number lower nibble
	romStream.read(&temp, 1);
	mapperNumber = ((temp & 0xF0) >> 4);
	trainerPresent = temp & 0x04;
	if (temp & 0x08) 
	{
		mirroring = Mapper::Mirroring::FourScreen;
	}
	else
	{
		mirroring = temp & 0x01 ?
			Mapper::Mirroring::Vertical :
			Mapper::Mirroring::Horizontal;
	}

	// Byte 7	NNNN xxPV
	//			||||   |*- vs unisystem
	//			||||   *-- pc10
	//			****------ Mapper number higher nibble
	romStream.read(&temp, 1);
	mapperNumber |= (temp & 0xF0);

	// Rest of header (reserved)
	romStream.seekg(8, std::ios_base::cur);

	if (trainerPresent)
	{
		m_cartridge.m_rom->m_trainer.resize(Cartridge::Rom::trainerSize);
		romStream.read(reinterpret_cast<char*>(m_cartridge.m_rom->m_trainer.data()), m_cartridge.m_rom->m_trainer.size());
	}
	romStream.read(reinterpret_cast<char*>(m_cartridge.m_rom->m_prgRom.data()), m_cartridge.m_rom->m_prgRom.size());
	romStream.read(reinterpret_cast<char*>(m_cartridge.m_rom->m_chrRom.data()), m_cartridge.m_rom->m_chrRom.size());

	*m_cartridge.m_mapper = m_mapperList[mapperNumber](mirroring);
}

void Nes::reset()
{
	m_cpu->reset();
}

void Nes::step()
{
	m_cpu->step();
}