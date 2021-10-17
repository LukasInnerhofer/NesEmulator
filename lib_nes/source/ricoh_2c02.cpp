#include "lib_nes/ricoh_2c02.h"

namespace LibNes
{

Ricoh2C02::Ricoh2C02() : 
    m_scanline{scanlineDefault},
    m_cycle{cycleDefault}
{

}

void Ricoh2C02::step()
{
    ++m_cycle;
    if (m_cycle > 340)
    {
        m_cycle = 0;

        ++m_scanline;
        if (m_scanline > 260)
        {
            m_scanline = -1;
        }
    }
}

uint16_t Ricoh2C02::getCycle()
{
    return m_cycle;
}

int16_t Ricoh2C02::getScanline()
{
    return m_scanline;
}

}