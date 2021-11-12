#ifndef RICOH_2C02_H
#define RICOH_2C02_H

#include <cstdint>
#include <memory>
#include <optional>

#include "libnes/mapper.h"
#include "libnes/screen.h"
#include "libutilities/non_null.h"

namespace LibNes
{

class Ricoh2C02
{
public:
    Ricoh2C02(NonNullSharedPtr<Screen> screen);

    void step();
    uint16_t getCycle();
    int16_t getScanline();

    void setMapper(NonNullSharedPtr<Mapper> mapper);

    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t data);

private:
    int16_t m_scanline;
    uint16_t m_cycle;
    NonNullSharedPtr<Screen> m_screen;
    std::optional<NonNullSharedPtr<Mapper>> m_mapper;

    std::vector<uint8_t> m_objectAttributeMemory;
    static constexpr size_t objectAttributeMemorySize{256};

    static constexpr int16_t scanlineDefault{241};
    static constexpr uint16_t cycleDefault{0};
};

} // namespace LibNes

#endif // RICOH_2C02_H
