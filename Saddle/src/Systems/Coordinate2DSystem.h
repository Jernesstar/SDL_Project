#pragma once

#include "Entity.h"
#include "Components.h"

namespace Saddle {

class Coordinate2DSystem {
public:
    void Translate(Entity& entity, int32_t delta_x, int32_t delta_y) 
    { 
        Coordinate2DComponent& coordinate2D_component = entity.GetComponent<Coordinate2DComponent>();
        coordinate2D_component.x += delta_x;
        coordinate2D_component.y += delta_y;
    }

    void PlaceAt(Entity& entity, uint32_t x, uint32_t y)
    {
        Coordinate2DComponent& coordinate2D_component = entity.GetComponent<Coordinate2DComponent>();
        coordinate2D_component.x = x;
        coordinate2D_component.y = y;
    }
};

}