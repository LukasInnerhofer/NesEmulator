#include "libnes/ricoh_2c02.h"

namespace LibNes
{

Ricoh2C02::Ricoh2C02(NonNullSharedPtr<Screen> screen) : 
    m_scanline{scanlineDefault},
    m_cycle{cycleDefault},
    m_screen{screen},
    m_objectAttributeMemory{objectAttributeMemorySize, std::allocator<uint8_t>{}}
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

void Ricoh2C02::setMapper(NonNullSharedPtr<Mapper> mapper)
{
    m_mapper = mapper;
}

uint8_t Ricoh2C02::read(uint16_t address) const
{
    uint8_t data{0};

    if (address <= 0x2FFF)
    {
        data = m_mapper.value()->read(address, Badge<Ricoh2C02>{});
    }

    return data;
}

void Ricoh2C02::write(uint16_t address, uint8_t data)
{

}

}