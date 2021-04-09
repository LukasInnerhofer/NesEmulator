#ifndef NES_H
#define NES_H

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <vector>

#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"
#include "mapper.h"
#include "nrom.h"

class Nes
{
public:
	Nes();

	void loadCartridge(std::istream& romStream);
	void step();
	void reset();

private:
	Cartridge m_cartridge;
	
	const std::vector<std::function<std::shared_ptr<Mapper>(const Mapper::Mirroring& mirroring)>> m_mapperList =
	{
		[&](const Mapper::Mirroring& mirroring) { return std::make_shared<NRom>(m_cartridge.m_rom, mirroring); }
	};

	std::unique_ptr<Cpu> m_cpu;
	std::shared_ptr<Ppu> m_ppu;
};

#endif // NES_H