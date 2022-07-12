#include "Circle.h"

namespace GameObjects {

Circle::Circle(uint32_t _radius, SDL_Color& _color, SDL_Renderer*& renderer, uint32_t _x = 0, uint32_t _y = 0)
{
    // radius = _radius;
    // color = _color;
    // center.x = _x;
    // center.y = _y;

    // SDL_Surface* circle_surface = (SDL_Surface*)malloc(sizeof(SDL_Surface));
    // Construct_Circle(circle_surface);
    // texture = SDL_CreateTextureFromSurface(renderer, circle_surface);
    
    // rect = circle_surface->clip_rect;
    // SDL_FreeSurface(circle_surface);
}

void Circle::SetPixel(SDL_Surface*& surface, int x, int y, uint32_t color)
{
  Uint32* const target_pixel = (Uint32*)((Uint8*)surface->pixels
                                            + y * surface->pitch
                                            + x * surface->format->BytesPerPixel);
  *(target_pixel) = color;
}

void Circle::Construct_Circle(SDL_Surface*& surface)
{
    uint32_t dx, dy;
    for(uint32_t w = 0; w <= radius * 2; w++)
    {
        for(uint32_t h = 0; h <= radius * 2; h++)
        {
            dx = radius - w; // horizontal offset
            dy = radius - h; // vertical offset
            if((dx * dx + dy * dy) <= (radius * radius))
            {
                uint32_t _color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
                SetPixel(surface, center.x + dx, center.y + dy, _color);
            }
       }
   }
}

}