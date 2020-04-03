#ifndef MAPPER_H
#define MAPPER_H

#include <memory>

#include "cartridge.h"

class Mapper
{
public:
	enum class Mirroring { Vertical, Horizontal, FourScreen };

	Mapper(const std::shared_ptr<Cartridge::Rom>& rom, const Mirroring& mirroring);

	virtual uint8_t read(const uint16_t& addr) = 0;
	virtual void write(const uint16_t& addr, const uint8_t& data) = 0;

protected:
	Mirroring m_mirroring;
	std::shared_ptr<Cartridge::Rom> m_rom;
};

#endif // MAPPER_H