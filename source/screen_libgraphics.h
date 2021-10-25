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
    ScreenLibGraphics(std::shared_ptr<LibGraphics::Window> window);

    void draw();
    void draw(LibNes::Screen::Pixel const &pixel) override;

private:
    std::shared_ptr<LibGraphics::Window> m_window;
    std::shared_ptr<LibGraphics::Texture> m_texture;
    LibGraphics::Rectangle m_rectangle;
};

}