#pragma once

#include "Saddle/Scene/Components.h"

namespace Saddle {

struct RGBColor {
    Uint8 r, g, b;
    
    RGBColor(Uint8 r, Uint8 b, Uint8 g) : r(r), b(b), g(g) { }
    RGBColor(const RGBColorComponent& component) : r(component.r), b(component.b), g(component.g) { }
};

}