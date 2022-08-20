#include "Renderer.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { s_Renderer = Application::Get().GetWindow().GetRenderer(); }

void Renderer::DrawTexture(Texture2D texture, Coordinate2D coordinate, Rect rect)
{
    SDL_Rect SDL_rect = { (int)coordinate.x, (int)coordinate.y, (int)rect.Width, (int)rect.Height };
    SDL_RenderCopy(s_Renderer, texture.m_Texture, nullptr, &SDL_rect);
}

void Renderer::SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
    Uint32 pixel_color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
    Uint32* pixel = (Uint32*)((Uint8*)surface->pixels 
                                    + (y * surface->pitch) 
                                    + (x * surface->format->BitsPerPixel));
    *pixel = pixel_color;
}

void Renderer::Render()
{
    SDL_RenderPresent(s_Renderer);
}

}