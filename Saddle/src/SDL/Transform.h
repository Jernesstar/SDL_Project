#pragma once

#include "Saddle/Core/Vector.h"
#include "Saddle/Scene/Components.h"

namespace Saddle {

struct Transform {
    Vector2D Coordinate = { 0.0f, 0.0f };
    float Rotation = 0;
    Vector2D Scale = { 1, 1 };

    Transform() = default;
    Transform(const TransformComponent& component)
        : Coordinate(component.Coordinate), Rotation(component.Rotation), Scale(component.Scale) { }
};

}