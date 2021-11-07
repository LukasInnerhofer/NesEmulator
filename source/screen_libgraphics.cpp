#include "screen_libgraphics.h"
#include <libgraphics/texture.h>

namespace NesEmulator
{

using namespace LibGraphics;

ScreenLibGraphics::ScreenLibGraphics(NonNullSharedPtr<Window> window) :
    m_texture{
        makeNonNullShared<Texture>(
            std::vector<uint8_t>(width * height * Texture::bytesPerPixel), 
            Texture::SizeVector{width, height})},
    m_rectangle{
        Vector<float>{-1.0f,-1.0f},
        Vector<float>{2.0f,2.0f},
        Color{0, 0, 0},
        m_texture},
    m_window{window}
{
    
}

void ScreenLibGraphics::draw()
{
    m_window->draw(m_rectangle);
}

void ScreenLibGraphics::draw(LibNes::Screen::Pixel const &pixel)
{
    m_texture->setPixel(
        Texture::PositionVector{pixel.position.x, pixel.position.y}, 
        Color{pixel.color.r, pixel.color.g, pixel.color.b});
}

}