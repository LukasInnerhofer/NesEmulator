#ifndef MAPPER_H
#define MAPPER_H

#include <memory>

#include "cartridge.h"

#include "libutilities/badge.h"

namespace LibNes
{

class CpuMemory;
class Ricoh2C02;

class Mapper
{
public:
	enum class Mirroring { Vertical, Horizontal, FourScreen };

	Mapper(NonNullSharedPtr<Cartridge::Rom> rom, const Mirroring& mirroring);

	virtual uint8_t read(
		uint16_t address, 
		Badge<CpuMemory>) = 0;
	virtual void write(
		uint16_t address, 
		uint8_t data, 
		Badge<CpuMemory>) = 0;

	virtual uint8_t read(
		uint16_t address, 
		Badge<Ricoh2C02>) = 0;
	virtual void write(
		uint16_t address, 
		uint8_t data, 
		Badge<Ricoh2C02>) = 0;

protected:
	Mirroring m_mirroring;
	NonNullSharedPtr<Cartridge::Rom> m_rom;
};

} // namespace LibNes

#endif // MAPPER_H
