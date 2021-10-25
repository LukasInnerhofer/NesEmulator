#ifndef MAPPER_H
#define MAPPER_H

#include <memory>

#include "cartridge.h"

namespace LibNes
{

class Mapper
{
public:
	enum class Mirroring { Vertical, Horizontal, FourScreen };

	Mapper(NonNullSharedPtr<Cartridge::Rom> rom, const Mirroring& mirroring);

	virtual uint8_t read(uint16_t addr) = 0;
	virtual void write(uint16_t addr, uint8_t data) = 0;

protected:
	Mirroring m_mirroring;
	NonNullSharedPtr<Cartridge::Rom> m_rom;
};

} // namespace LibNes

#endif // MAPPER_H
