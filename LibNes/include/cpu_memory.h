#ifndef CPU_MEMORY_H
#define CPU_MEMORY_H

#include <memory>
#include <vector>

#include "mapper.h"
#include "mos6502_memory.h"

class CpuMemory : public LibMos6502::Memory
{
public:
	CpuMemory(std::shared_ptr<std::vector<uint8_t>> ram, std::shared_ptr<std::unique_ptr<Mapper>> mapper);

	uint8_t read(uint16_t addr) override;
	void write(uint16_t addr, uint8_t data) override;

private:
	std::shared_ptr<std::vector<uint8_t>> m_ram;
	std::shared_ptr<std::unique_ptr<Mapper>> m_mapper;
};

#endif // CPU_MEMORY_H