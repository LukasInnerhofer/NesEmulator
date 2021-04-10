#include "mapper.h"

Mapper::Mapper(const std::shared_ptr<Cartridge::Rom>& rom, const Mirroring& mirroring) : m_rom(rom), m_mirroring(mirroring)
{

}