#pragma once

#include "GameObject.h"

#include <SDL.h>

namespace GameObjects {
// Class used to represent a circle
class Circle : GameObject {

public:
    Circle(uint32_t radius, uint32_t x = 0, uint32_t y = 0);

};

}