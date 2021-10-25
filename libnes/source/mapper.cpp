#include "libnes/mapper.h"

namespace LibNes
{

Mapper::Mapper(NonNullSharedPtr<Cartridge::Rom> rom, const Mirroring& mirroring) : 
    m_rom{rom}, 
    m_mirroring{mirroring}
{

}

} // namespace LibNes
