#pragma once

#include "Saddle/Scene/Components.h"

namespace Saddle {

struct Rect {
    int Width, Height;

    Rect(int width, int height) : Width(width), Height(height) { }
    Rect(const RectComponent& component) : Width(component.Width), Height(component.Height) { } 
};

}