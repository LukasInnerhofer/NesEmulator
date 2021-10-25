#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <functional>
#include <memory>

#include "libutilities/non_null.h"

namespace LibNes
{

class Mapper;

struct Cartridge
{
	struct Rom
	{
		std::vector<uint8_t> m_trainer;
		std::vector<uint8_t> m_prgRom;
		std::vector<uint8_t> m_chrRom;

		static constexpr size_t headerSize{4};
		static constexpr char header[headerSize + 1]{'N', 'E', 'S', 0x1A, 0};
		static constexpr size_t trainerSize{512};
		static constexpr size_t prgRomSizeMultiplier{16384};
		static constexpr size_t chrRomSizeMultiplier{8192};

		Rom(
			std::vector<uint8_t>&& trainer, 
			std::vector<uint8_t>&& prgRom, 
			std::vector<uint8_t>&& chrRom) :
			m_trainer{std::move(trainer)}, 
			m_prgRom{std::move(prgRom)}, 
			m_chrRom{std::move(chrRom)}
		{

		}
	};

	NonNullSharedPtr<Rom> m_rom;
	NonNullSharedPtr<Mapper> m_mapper;

	Cartridge(
		std::vector<uint8_t>&& trainer, 
		std::vector<uint8_t>&& prgRom, 
		std::vector<uint8_t>&& chrRom, 
		std::function<NonNullSharedPtr<Mapper>(NonNullSharedPtr<Rom>)> mapper) :
		m_rom{std::make_shared<Rom>(std::move(trainer), std::move(prgRom), std::move(chrRom))},
		m_mapper{mapper(m_rom)}
	{
		
	}
};

} // namespace LibNes

#endif // CARTRIDGE_H
