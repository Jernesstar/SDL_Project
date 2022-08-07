#pragma once

#include "Entity.h"
#include "Components.h"

namespace Saddle {

class RectSystem {

public:
    void Scale(Entity& entity, int32_t scalar)
    {  
        RectComponent& rect_component = entity.GetComponent<RectComponent>();
        rect_component.width *= scalar;
        rect_component.height *= scalar;
    }
};

}