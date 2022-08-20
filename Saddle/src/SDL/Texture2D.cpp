#include "Texture2D.h"

#include <iostream>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

Texture2D::Texture2D(SDL_Surface* surface)
    : m_Width(surface->w), m_Height(surface->h)
{
    // Note: Move Window::m_Renderer to Renderer class
    auto renderer = Application::Get().GetWindow().GetRenderer();
    m_Texture = SDL_CreateTextureFromSurface(renderer, surface);

    SADDLE_CORE_ASSERT(m_Texture != nullptr, "Could not create texture");
}

Texture2D::~Texture2D() { if(m_Texture) SDL_DestroyTexture(m_Texture); }

}