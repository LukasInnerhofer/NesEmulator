#include "libnes/ricoh_2c02.h"

namespace LibNes
{

Ricoh2C02::Ricoh2C02(NonNullSharedPtr<Screen> screen) : 
    m_scanline{scanlineDefault},
    m_cycle{cycleDefault},
    m_screen{screen}
{
}

void Ricoh2C02::step()
{
    static uint64_t time = 0;
    Screen::Pixel pixel;
    pixel.position = {m_cycle, static_cast<uint16_t>(m_scanline)};
    pixel.color = { static_cast<uint8_t>((m_cycle / 340.f) * 0xFF), static_cast<uint8_t>(time), static_cast<uint8_t>((m_scanline / 260.f) * 0xFF) };
    m_screen->draw(pixel);
    ++m_cycle;
    if (m_cycle > 340)
    {
        m_cycle = 0;

        ++m_scanline;
        if (m_scanline > 260)
        {
            m_scanline = -1;
            time++;
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