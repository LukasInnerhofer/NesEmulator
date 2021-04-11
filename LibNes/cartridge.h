#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <memory>

class Mapper;

struct Cartridge
{
	struct Rom
	{
		std::vector<uint8_t> m_trainer = std::vector<uint8_t>();
		std::vector<uint8_t> m_prgRom = std::vector<uint8_t>();
		std::vector<uint8_t> m_chrRom = std::vector<uint8_t>();

		static constexpr size_t headerSize = 4;
		static constexpr char header[headerSize + 1] = { 'N', 'E', 'S', 0x1A, 0 };
		static constexpr size_t trainerSize = 512;
		static constexpr size_t prgRomSizeMultiplier = 16384;
		static constexpr size_t chrRomSizeMultiplier = 8192;
	};

	std::shared_ptr<Rom> m_rom = std::make_shared<Rom>();
	std::shared_ptr<std::unique_ptr<Mapper>> m_mapper = std::make_shared<std::unique_ptr<Mapper>>();
};

#endif // CARTRIDGE_H