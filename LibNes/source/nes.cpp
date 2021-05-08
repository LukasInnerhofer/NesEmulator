#include <cstring>
#include <thread>

#include "nes.h"
#include "cpu_memory.h"

namespace LibNes
{

Nes::Nes()
{
	m_cartridge = nullptr;
	m_ram = std::make_shared<std::vector<uint8_t>>(ramSize);
	m_cpuMemory = std::make_shared<CpuMemory>(m_ram);
	m_cpu = std::make_unique<LibMos6502::Mos6502>(m_cpuMemory);
}

void Nes::loadCartridge(std::istream& romStream)
{
	// Determine stream size
	romStream.seekg(0, std::ios_base::end);
	std::streampos size{romStream.tellg()};

	romStream.seekg(0, std::ios_base::beg);

	{
		// Validate header
		char header[Cartridge::Rom::headerSize + 1];
		romStream.read(header, Cartridge::Rom::headerSize);
		header[sizeof(header) - 1] = 0;
		if (std::strcmp(header, Cartridge::Rom::header) != 0)
		{
			// TODO: Handle invalid header.
			return;
		}
	}

	char temp;
	// Determine prg & chr ROM size
	romStream.read(&temp, 1);
	auto prgRom{std::vector<uint8_t>(temp * Cartridge::Rom::prgRomSizeMultiplier)};
	romStream.read(&temp, 1);
	auto chrRom{std::vector<uint8_t>(temp * Cartridge::Rom::chrRomSizeMultiplier)};

	// Byte 6	NNNN FTBM
	//			|||| |||*- Mirroring (if not four screen)
	//			|||| ||*-- ?
	//			|||| |*--- Trainer present
	//			|||| *---- Four screen mirroring
	//			****------ Mapper number lower nibble
	romStream.read(&temp, 1);
	auto mapperNumber{static_cast<size_t>((temp & 0xF0) >> 4)};
	auto trainerPresent{static_cast<bool>(temp & 0x04)};
	Mapper::Mirroring mirroring;
	if (temp & 0x08) 
	{
		mirroring = Mapper::Mirroring::FourScreen;
	}
	else
	{
		mirroring = temp & 0x01 ?
			Mapper::Mirroring::Vertical :
			Mapper::Mirroring::Horizontal;
	}

	// Byte 7	NNNN xxPV
	//			||||   |*- vs unisystem
	//			||||   *-- pc10
	//			****------ Mapper number higher nibble
	romStream.read(&temp, 1);
	mapperNumber |= (temp & 0xF0);

	// Rest of header (reserved)
	romStream.seekg(8, std::ios_base::cur);

	std::vector<uint8_t> trainer;
	if (trainerPresent)
	{
		trainer.resize(Cartridge::Rom::trainerSize);
		romStream.read(reinterpret_cast<char*>(trainer.data()), trainer.size());
	}
	romStream.read(reinterpret_cast<char*>(prgRom.data()), prgRom.size());
	romStream.read(reinterpret_cast<char*>(chrRom.data()), chrRom.size());

	m_cartridge = std::make_unique<Cartridge>(
		std::move(trainer),
		std::move(prgRom), 
		std::move(chrRom), 
		[&](std::shared_ptr<Cartridge::Rom> rom) { return m_mapperList[mapperNumber](rom, mirroring); });
	m_cpuMemory->setMapper(m_cartridge->m_mapper);
}

void Nes::reset()
{
	m_cpu->reset();
}

void Nes::runFor(std::chrono::nanoseconds time)
{
	const std::chrono::time_point start = std::chrono::steady_clock::now();
	for(int64_t iterations{time / cpuCycleTime}; iterations > 0; iterations -= m_cpu->getCycles())
	{
		m_cpu->step();
	}
	std::this_thread::sleep_until(start + time);
}

} // namespace LibNes
