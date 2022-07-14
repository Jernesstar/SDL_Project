#include "Circle.h"

#include <iostream>

namespace GameObjects {

Circle::Circle() { }

Circle::Circle(uint32_t _radius, SDL_Color& _color, uint32_t _x = 0, uint32_t _y = 0) :
GameObject()
{
    radius = _radius;
    color = _color;
    center.x = _x;
    center.y = _y;
}

void Circle::Construct_Circle(SDL_Renderer* renderer)
{  
    int flags = 0;
    int depth = 32;
    SDL_Surface* surface = SDL_CreateRGBSurface(flags, 2 * radius, 2 * radius, depth, 0, 0, 0, 0);
    
    uint32_t dx, dy;
    uint32_t _color = SDL_MapRGB(surface->format, color.r, color.g, color.b);

    for(uint32_t w = 0; w <= radius * 2; w++)
    {
        for(uint32_t h = 0; h <= radius * 2; h++)
        {
            dx = radius - w; // horizontal offset
            dy = radius - h; // vertical offset
            if((dx * dx + dy * dy) <= (radius * radius))
            {
                SetPixel(surface, center.x + dx, center.y + dy, _color);
            }
        }
    }

    int diameter = 2 * radius;
    int coord = center.x - radius;
    rect = {diameter, diameter, coord, coord};
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

}