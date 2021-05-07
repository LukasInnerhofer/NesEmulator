#include "mapper.h"

namespace LibNes
{

Mapper::Mapper(std::shared_ptr<Cartridge::Rom> rom, const Mirroring& mirroring) : m_rom(rom), m_mirroring(mirroring)
{

}

} // namespace LibNes
