#pragma once

#include <cstdint>

namespace LibNes
{

class Screen
{
public:
    size_t constexpr static width = 256;
    size_t constexpr static height = 240;

    typedef struct
    {
        typedef struct
        {
            uint8_t r, g, b;
        } Color;
        Color color;

        typedef struct
        {
            uint16_t x, y;
        } Position;
        Position position;
    } Pixel;
    
    virtual void draw(Pixel const &pixel) = 0;
};

}