#pragma once

#include "libgraphics/rectangle.h"
#include "libgraphics/window.h"

#include "libnes/screen.h"

namespace NesEmulator
{

class ScreenLibGraphics : public LibNes::Screen
{
public:
    ScreenLibGraphics() = delete;
    ScreenLibGraphics(NonNullSharedPtr<LibGraphics::Window> window);

    void draw();
    void draw(LibNes::Screen::Pixel const &pixel) override;

private:
    NonNullSharedPtr<LibGraphics::Window> m_window;
    NonNullSharedPtr<LibGraphics::Texture> m_texture;
    LibGraphics::Rectangle m_rectangle;
};

}