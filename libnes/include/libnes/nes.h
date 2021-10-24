#ifndef NES_H
#define NES_H

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <vector>

#if defined(LIB_NES_LOG)
#include <fstream>
#endif

#include "cpu_memory.h"
#include "libmos6502/mos6502.h"
#include "libnes/ricoh_2c02.h"
#include "libnes/cartridge.h"
#include "libnes/mapper.h"
#include "libnes/nrom.h"

namespace LibNes
{

class Nes
{
public:
	Nes(std::shared_ptr<Screen> screen);

	void loadCartridge(std::istream& romStream);
	void runFor(std::chrono::nanoseconds time
#if defined(LIB_NES_LOG)
		, std::ofstream& log
#endif
	);
	void reset();

private:
	std::shared_ptr<std::vector<uint8_t>> m_ram;
	static constexpr size_t ramSize{0x800};

	std::unique_ptr<Cartridge> m_cartridge;
	
	const std::vector<
		std::function<
			std::shared_ptr<Mapper>(
				std::shared_ptr<Cartridge::Rom>, 
				Mapper::Mirroring)>> m_mapperList
	{
		[&](std::shared_ptr<Cartridge::Rom> rom, Mapper::Mirroring mirroring) { return std::make_shared<NRom>(rom, mirroring); }
	};

	std::shared_ptr<CpuMemory> m_cpuMemory;
	std::unique_ptr<LibMos6502::Mos6502> m_cpu;
	static constexpr std::chrono::nanoseconds cpuCycleTime{static_cast<uint16_t>(1000000000. / 1790000)}; // 1/(1.79 MHz)
	std::unique_ptr<Ricoh2C02> m_ppu;
};

} // namespace LibNes

#endif // NES_H
