#ifndef NES_H
#define NES_H

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <vector>

#include "mos6502.h"
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
	std::shared_ptr<std::vector<uint8_t>> m_ram;
	static constexpr size_t ramSize = 0x800;

	Cartridge m_cartridge;
	
	const std::vector<std::function<Mapper*(const Mapper::Mirroring& mirroring)>> m_mapperList =
	{
		[&](const Mapper::Mirroring& mirroring) { return new NRom(m_cartridge.m_rom, mirroring); }
	};

	std::unique_ptr<LibMos6502::Mos6502> m_cpu;
	std::shared_ptr<Ppu> m_ppu;
};

#endif // NES_H