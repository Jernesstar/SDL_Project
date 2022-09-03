#pragma once

#include "SDL/Font.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {


// Todo: Set up the dependencies of all systems in a visible way
// struct TextureSystemDependencies {

// };

class TextureSystem {
public:
    static void CreateText(Entity& entity, const std::string& text, Font& font);
    static void CreateRectangle(Entity& entity, int width, int height, int depth = 32, 
        int r_mask = 0, int g_mask = 0, int b_mask = 0, int a_mask = 0);
    static void CreateCircle(Entity& entity, int radius);
};

}