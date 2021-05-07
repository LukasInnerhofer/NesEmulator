#include "nrom.h"

namespace LibNes
{

uint8_t NRom::read(uint16_t addr)
{
	uint8_t data = 0;

	if (addr <= 0x1FFF)			// CHR ROM
	{
		if (addr < m_rom->m_chrRom.size() - 1)
		{
			data = m_rom->m_chrRom[addr];
		}
	}

	else if (addr <= 0x3EFF)	// TODO: Nametables
	{

	}

	else if (addr <= 0x7FFF)	// TODO: Invalid address
	{

	}

	else						// PRG ROM
	{
		data = m_rom->m_prgRom[addr - 0x8000];
	}

	return data;
}

void NRom::write(uint16_t addr, uint8_t data)
{
	
}

} // namespace LibNes
