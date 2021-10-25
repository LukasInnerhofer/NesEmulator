#ifndef CPU_MEMORY_H
#define CPU_MEMORY_H

#include <memory>
#include <optional>
#include <vector>

#include "libmos6502/memory.h"
#include "libutilities/non_null.h"

#include "mapper.h"

namespace LibNes
{

class CpuMemory : public LibMos6502::Memory
{
public:
	CpuMemory(NonNullSharedPtr<std::vector<uint8_t>> ram);

	uint8_t read(uint16_t addr) override;
	void write(uint16_t addr, uint8_t data) override;

	void setMapper(NonNullSharedPtr<Mapper> mapper);

private:
	NonNullSharedPtr<std::vector<uint8_t>> m_ram;
	std::optional<NonNullSharedPtr<Mapper>> m_mapper;
};

}

#endif // CPU_MEMORY_H
