#pragma once

#include "Saddle/Core/Assert.h"
#include "Saddle/Scene/Components.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {

class RectSystem {
public:
    void Scale(Entity& entity, int32_t scalar)
    {
        SADDLE_CORE_ASSERT(entity.HasComponent<RectComponent>());
        RectComponent& rect_component = entity.GetComponent<RectComponent>();
        rect_component.Width *= scalar;
        rect_component.Height *= scalar;
    }
};

}