#include "Circle.h"

#include <iostream>

namespace GameObjects {

Circle::Circle(uint32_t _radius, SDL_Color& _color, SDL_Renderer*& renderer, uint32_t _x = 0, uint32_t _y = 0)
{
    radius = _radius;
    color = _color;
    center.x = _x;
    center.y = _y;

    int flags, paddle_width, paddle_height, depth;
    flags = 0;
    depth = 32;
    
    SDL_Surface* circle_surface = SDL_CreateRGBSurface(flags, 2 * radius, 2 * radius, 32, 0, 0, 0, 0);
    Construct_Circle(circle_surface);
    texture = SDL_CreateTextureFromSurface(renderer, circle_surface);
    
    SDL_FreeSurface(circle_surface);
}

void Circle::SetPixel(SDL_Surface* surface, uint8_t x, uint8_t y, uint32_t color)
{
    uint32_t* target_pixel = (uint32_t*)((uint8_t*)surface->pixels 
                                            + y * surface->pitch 
                                            + x * surface->format->BytesPerPixel);
    *target_pixel = color;
}

void Circle::Construct_Circle(SDL_Surface* surface)
{  
    uint32_t dx, dy;
    Uint32 _color = SDL_MapRGB(surface->format, color.r, color.g, color.b);

    for(uint32_t w = 0; w <= radius * 2; w++)
    {
        for(uint32_t h = 0; h <= radius * 2; h++)
        {
            dx = radius - w; // horizontal offset
            dy = radius - h; // vertical offset
            if((dx * dx + dy * dy) <= (radius * radius))
            {
                SetPixel(surface, (uint8_t)(center.x + dx), (uint8_t)(center.y + dy), _color); //
            }
       }
   }
}

}