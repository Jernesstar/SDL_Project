#include "Renderer.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { s_Renderer = Application::Get().GetWindow().GetRenderer(); }

void Renderer::Clear() { SDL_RenderClear(s_Renderer); }

void Renderer::DrawTexture(const Texture2D& texture, const Transform& transform)
{
    SADDLE_CORE_ASSERT(texture.m_Texture != nullptr, "Texture is invalid");

    const Vector2D& coordinate = transform.Coordinate;
    const Vector2D& scale = transform.Scale;
    SDL_FRect rect = { coordinate.x, coordinate.y, texture.Width * scale.x, texture.Height * scale.y };
    SDL_RenderCopyExF(s_Renderer, texture.m_Texture, nullptr, &rect, transform.Rotation, nullptr, SDL_FLIP_NONE);
}

void Renderer::Render() { SDL_RenderPresent(s_Renderer); }

void Renderer::SetPixel(SDL_Surface* surface, int x, int y, RGBColor color)
{
    Uint32 pixel_color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
    Uint32* pixel = (Uint32*)((Uint8*)surface->pixels 
                                    + (y * surface->pitch) 
                                    + (x * surface->format->BitsPerPixel));
    *pixel = pixel_color;
}

}