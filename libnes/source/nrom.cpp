#include <cassert>

#include "libnes/nrom.h"

namespace LibNes
{

NRom::NRom(
	NonNullSharedPtr<Cartridge::Rom> rom, 
	const Mirroring& mirroring,
	NonNullSharedPtr<std::vector<uint8_t>> vram) :
	Mapper{rom, mirroring},
	m_vram{vram}
{
}

uint8_t NRom::read(uint16_t address, Badge<CpuMemory>)
{
	uint8_t data{0};

	assert(address >= 0x4020);

	if (address >= 0x6000 && address <= 0x7FFF) // TODO: PRG RAM
	{

	}

	else // PRG ROM
	{
		data = m_rom->m_prgRom[(address - 0x8000) % m_rom->m_prgRom.size()];
	}

	return data;
}

void NRom::write(uint16_t address, uint8_t data, Badge<CpuMemory>)
{
	
}

uint8_t NRom::read(uint16_t address, Badge<Ricoh2C02>)
{
	uint8_t data{0};

	if (address <= 0x1FFF)
	{
		data = m_rom->m_chrRom[address];
	}
	else if (address <= 0x2FFF)
	{
		if (m_mirroring == Mirroring::Horizontal)
		{
			if (address <= 0x27FF)
			{
				data = m_vram->data()[(address - 0x2000) % 0x400];
			}
			else
			{
				data = m_vram->data()[((address - 0x2800) % 0x400) + 0x800];
			}
		}
		else if (m_mirroring == Mirroring::Vertical)
		{
			data = m_vram->data()[(address - 0x2000) % 0x800];
		}
	}
	else if (address <= 0x3EFF)
	{
		// TODO: mirror 0x2000
	}

	return data;
}

void NRom::write(uint16_t address, uint8_t data, Badge<Ricoh2C02>)
{
	
}

} // namespace LibNes
