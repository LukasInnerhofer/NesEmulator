#ifndef NES_H
#define NES_H

#include "libutilities/non_null.h"
#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <vector>

#if defined(LIBNES_LOG)
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
	Nes(NonNullSharedPtr<Screen> screen);

	void loadCartridge(std::istream& romStream);
	void runFor(std::chrono::nanoseconds time
#if defined(LIBNES_LOG)
		, std::ofstream& log
#endif
	);
	void reset();

private:
	NonNullSharedPtr<std::vector<uint8_t>> m_ram;
	static constexpr size_t ramSize{0x800};

	std::optional<NonNullUniquePtr<Cartridge>> m_cartridge;
	
	const std::vector<
		std::function<
			NonNullSharedPtr<Mapper>(
				NonNullSharedPtr<Cartridge::Rom>, 
				Mapper::Mirroring)>> m_mapperList
	{
		[&](NonNullSharedPtr<Cartridge::Rom> rom, Mapper::Mirroring mirroring) { return std::make_shared<NRom>(rom, mirroring); }
	};

	NonNullSharedPtr<CpuMemory> m_cpuMemory;
	NonNullUniquePtr<LibMos6502::Mos6502> m_cpu;
	static constexpr std::chrono::nanoseconds cpuCycleTime{static_cast<uint16_t>(1000000000. / 1790000)}; // 1/(1.79 MHz)
	NonNullUniquePtr<Ricoh2C02> m_ppu;
};

} // namespace LibNes

#endif // NES_H
