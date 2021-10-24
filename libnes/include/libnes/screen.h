#pragma once

#include <cstdint>

namespace LibNes
{

class Screen
{
public:
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