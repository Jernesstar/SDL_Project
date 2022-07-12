#pragma once

#include "GameObject.h"

#include <SDL.h>

namespace GameObjects {
// Class used to represent a circle
class Circle : GameObject {

public:
    Circle();    
    Circle(uint32_t _radius, SDL_Color& _color, SDL_Renderer*& renderer, uint32_t _x, uint32_t _y);
    
    void Construct_Circle(SDL_Surface*& surface);
    void SetPixel(SDL_Surface*& surface, int x, int y, uint32_t pixel);

private:
    uint32_t radius;
};

}