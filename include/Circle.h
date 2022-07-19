#pragma once

#include "GameObject.h"

namespace Saddle::GameObjects {
    
    // Class used to represent a circle
    class Circle : public GameObject {

    public:
        Circle();
        Circle(uint32_t _radius, SDL_Color& _color, SDL_Renderer* renderer, uint32_t _x, uint32_t _y);
        
    private:
        uint32_t radius;

    private:
        void Construct_Circle(SDL_Renderer* renderer);
    };

}