#include "Renderer.h"
#include "Application.h"

namespace Saddle {

void Renderer::Init() { s_Renderer = Application::Get().GetWindow().GetRenderer(); }

void Renderer::DrawTexture(SDL_Rect& rect, SDL_Texture* texture)
{
    SDL_RenderCopy(s_Renderer, texture, nullptr, &rect);
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