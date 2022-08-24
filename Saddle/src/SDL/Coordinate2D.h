#pragma once

#include "Saddle/Scene/Components.h"

namespace Saddle {

struct Coordinate2D {
    float x, y;

    Coordinate2D(float x, float y) : x(x), y(y) { }
    Coordinate2D(const Coordinate2DComponent& component) : x(component.x), y(component.y) { }
};

}