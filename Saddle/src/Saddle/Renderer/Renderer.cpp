#include "Renderer.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { s_Renderer = Application::Get().GetWindow().GetRenderer(); }

void Renderer::Clear() { SDL_RenderClear(s_Renderer); }

void Renderer::DrawTexture(Texture2D& texture, Coordinate2D coordinate)
{
    SADDLE_CORE_ASSERT(texture.m_Texture != nullptr, "Texture is invalid");

    SDL_FRect rect = { coordinate.x, coordinate.y, texture.Width, texture.Height };
    SDL_RenderCopyExF(s_Renderer, texture.m_Texture, nullptr, &rect, texture.Angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Render() { SDL_RenderPresent(s_Renderer); }

void Renderer::SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
    Uint32 pixel_color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
    Uint32* pixel = (Uint32*)((Uint8*)surface->pixels 
                                    + (y * surface->pitch) 
                                    + (x * surface->format->BitsPerPixel));
    *pixel = pixel_color;
}

}