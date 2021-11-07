#include <cassert>

#include "libnes/cpu_memory.h"

namespace LibNes
{

CpuMemory::CpuMemory(NonNullSharedPtr<std::vector<uint8_t>> ram) :
	m_ram{ram}, m_mapper{}
{

}

uint8_t CpuMemory::read(uint16_t addr)
{
	uint8_t data{0};

	if (addr <= 0x1FFF) // Internal RAM
	{
		data = m_ram->at(addr % m_ram->size());
	}

	else if (addr <= 0x3FFF) // TODO: PPU Registers
	{

	}

	else if (addr <= 0x4017) // TODO: NES API and I/O registers
	{

	}

	else if (addr <= 0x401F) // TODO: API and I/O functionality that is normally disabled.
	{

	}

	else if (addr <= 0xFFFF) // Cartridge space
	{
		assert(m_mapper);
		data = m_mapper.value()->read(addr);
	}

	return data;
}

void CpuMemory::write(uint16_t addr, uint8_t data)
{
	if (addr <= 0x1FFF) // Internal RAM
	{
		m_ram->at(addr % m_ram->size()) = data;
	}

	else if (addr <= 0x3FFF) // TODO: PPU Register (addr % 8)
	{

	}

	else if (addr <= 0x4017) // TODO: NES API and I/O registers
	{

	}

	else if (addr <= 0x401F) // TODO: API and I/O functionality that is normally disabled.
	{

	}

	else // Cartridge space
	{
		assert(m_mapper);
		m_mapper.value()->write(addr, data);
	}
}

void CpuMemory::setMapper(NonNullSharedPtr<Mapper> mapper)
{
	m_mapper = mapper;
}

} // namespace LibNes
