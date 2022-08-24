#pragma once

#include "Saddle/Scene/Components.h"

namespace Saddle {

struct Rect {
    float Width, Height;

    Rect(float width, float height) : Width(width), Height(height) { }
    Rect(const RectComponent& component) : Width(component.Width), Height(component.Height) { } 
};

}