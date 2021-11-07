#pragma once

#include <cstdint>

namespace LibNes
{

class Screen
{
public:
    size_t constexpr static width = 256;
    size_t constexpr static height = 240;

    struct Pixel
    {
        struct Color
        {
            uint8_t r, g, b;
        };
        Color color;

        struct Position
        {
            uint16_t x, y;
        };
        Position position;
    };
    
    virtual void draw(Pixel const &pixel) = 0;
};

}