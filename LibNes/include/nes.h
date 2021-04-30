#ifndef NES_H
#define NES_H

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <vector>

#include "cpu_memory.h"
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

	std::unique_ptr<Cartridge> m_cartridge;
	
	const std::vector<std::function<std::shared_ptr<Mapper>(std::shared_ptr<Cartridge::Rom>, Mapper::Mirroring)>> m_mapperList =
	{
		[&](std::shared_ptr<Cartridge::Rom> rom, Mapper::Mirroring mirroring) { return std::make_shared<NRom>(rom, mirroring); }
	};

	std::shared_ptr<CpuMemory> m_cpuMemory;
	std::unique_ptr<LibMos6502::Mos6502> m_cpu;
	std::shared_ptr<Ppu> m_ppu;
};

#endif // NES_H