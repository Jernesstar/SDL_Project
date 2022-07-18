#pragma once

#include "GameObject.h"

namespace GameObjects {
    
    // Class used to represent a circle
    class Circle : public GameObject {

    public:
        Circle();
        Circle(uint32_t _radius, SDL_Color& _color, uint32_t _x, uint32_t _y);
        
        void Construct_Circle(SDL_Renderer* renderer);

    private:
        uint32_t radius;
    };

}