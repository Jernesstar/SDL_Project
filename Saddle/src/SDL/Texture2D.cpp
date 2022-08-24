#include "Texture2D.h"

#include <iostream>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

Texture2D::Texture2D(SDL_Surface* surface, double angle)
    : Width(surface->w), Height(surface->h), Angle(angle)
{
    // Note: Maybe move Window::m_Renderer to Renderer class
    auto renderer = Application::Get().GetWindow().GetRenderer();
    m_Texture = SDL_CreateTextureFromSurface(renderer, surface);

    SADDLE_CORE_ASSERT(m_Texture != nullptr, "Could not create texture");
}

Texture2D::Texture2D(Texture2D&& other)
    : Width(other.Width), Height(other.Height), Angle(other.Angle), m_Texture(other.m_Texture)
{ other.m_Texture = nullptr; }

Texture2D::~Texture2D() { if(m_Texture) SDL_DestroyTexture(m_Texture); }

Texture2D& Texture2D::operator=(Texture2D&& other)
{
    if(this == &other) return *this;
    if(m_Texture) SDL_DestroyTexture(m_Texture);

    this->Width  = other.Width;
    this->Height = other.Height;
    this->Angle  = other.Angle;
    this->m_Texture = other.m_Texture;

    other.m_Texture = nullptr;
    return *this;
}

}