#ifndef NROM_H
#define NROM_H

#include "mapper.h"

namespace LibNes
{

class NRom : public Mapper
{
public:
	NRom(
		NonNullSharedPtr<Cartridge::Rom> rom, 
		const Mirroring& mirroring,
		NonNullSharedPtr<std::vector<uint8_t>> vram);

	uint8_t read(
		uint16_t address, 
		Badge<CpuMemory>) override;
	void write(
		uint16_t address, 
		uint8_t data, 
		Badge<CpuMemory>) override;

	uint8_t read(
		uint16_t address, 
		Badge<Ricoh2C02>) override;
	void write(
		uint16_t address, 
		uint8_t data, 
		Badge<Ricoh2C02>) override;

private:
	NonNullSharedPtr<std::vector<uint8_t>> m_vram;
};

} // namespace LibNes

#endif // NROM_H
