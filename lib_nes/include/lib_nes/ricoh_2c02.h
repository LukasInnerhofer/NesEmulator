#ifndef RICOH_2C02_H
#define RICOH_2C02_H

#include <cstdint>

namespace LibNes
{

class Ricoh2C02
{
public:
    Ricoh2C02();

    void step();
    uint16_t getCycle();
    int16_t getScanline();

private:
    int16_t m_scanline;
    uint16_t m_cycle;

    static constexpr int16_t scanlineDefault{241};
    static constexpr uint16_t cycleDefault{0};
};

} // namespace LibNes

#endif // RICOH_2C02_H
