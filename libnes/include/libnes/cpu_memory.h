#ifndef CPU_MEMORY_H
#define CPU_MEMORY_H

#include <memory>
#include <vector>

#include "mapper.h"
#include "libmos6502/memory.h"

namespace LibNes
{

class CpuMemory : public LibMos6502::Memory
{
public:
	CpuMemory(std::shared_ptr<std::vector<uint8_t>> ram);

	uint8_t read(uint16_t addr) override;
	void write(uint16_t addr, uint8_t data) override;

	void setMapper(std::shared_ptr<Mapper> mapper);

private:
	std::shared_ptr<std::vector<uint8_t>> m_ram;
	std::shared_ptr<Mapper> m_mapper;
};

}

#endif // CPU_MEMORY_H
