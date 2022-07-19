#include "Circle.h"

namespace Saddle::GameObjects {

Circle::Circle() { }

Circle::Circle(uint32_t _radius, SDL_Color& _color, SDL_Renderer* renderer, uint32_t _x = 0, uint32_t _y = 0) :
GameObject()
{
    radius = _radius;
    color = _color;
    center.x = _x;
    center.y = _y;

    int diameter = 2 * radius;
    int x = center.x - radius;
    int y = center.y - radius;
    rect = {x, y, diameter, diameter};

    Construct_Circle(renderer);
}

void Circle::Construct_Circle(SDL_Renderer* renderer)
{  
    int flags = 0;
    int depth = 32;
    int _radius = (int)radius;

    SDL_Surface* surface = SDL_CreateRGBSurface(flags, 2 * _radius, 2 * _radius, depth, 0, 0, 0, 0);
    SDL_LockSurface(surface);

    int dx, dy;
    for(int w = 0; w < surface->w; w++)
    {
        for(int h = 0; h < surface->h; h++)
        {
            dx = _radius - w; // horizontal offset
            dy = _radius - h; // vertical offset
            if((dx * dx + dy * dy) <= (_radius * _radius))
            {
                SetPixel(surface, (surface->w * 0.5) + dx, (surface->h * 0.5) + dy, color);
            }
        }
    }
    
    SDL_UnlockSurface(surface);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

}
