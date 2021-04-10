#ifndef NROM_H
#define NROM_H

#include "mapper.h"

class NRom : public Mapper
{
public:
	using Mapper::Mapper;

	uint8_t read(uint16_t addr) override;
	void    write(uint16_t addr, uint8_t data) override;
};

#endif // NROM_H