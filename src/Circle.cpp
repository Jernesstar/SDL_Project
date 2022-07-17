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
    int _radius = (int)radius;

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(flags, depth * 2 * _radius, depth * 2 * _radius, depth, SDL_PIXELFORMAT_RGBA32);
    SDL_LockSurface(surface);

    int dx, dy;
    // for(int w = 0; w < _radius * 2; w++)
    // {
    //     for(int h = 0; h < _radius * 2; h++)
    //     {
    //         dx = _radius - w; // horizontal offset
    //         dy = _radius - h; // vertical offset
    //         if((dx * dx + dy * dy) <= (_radius * _radius))
    //         {
    //             SetPixel(surface, dx, dy, color);
    //         }
    //     }
    // }
    for(int w = 0; w < _radius * 4; w++)
    {
        for(int h = 0; h < _radius * 4; h++)
        {
            SetPixel(surface, h, w, color);
        }
    }


    int diameter = 2 * _radius;
    int x = center.x - _radius;
    int y = center.y - _radius;
    rect = {x, y, diameter, diameter};

    SDL_UnlockSurface(surface);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

}