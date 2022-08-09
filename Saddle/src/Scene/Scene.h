#pragma once

#include "Entity.h"

#include <iostream>
#include <vector>
#include <functional>

namespace Saddle {

class Scene {

public:
    Scene();
    ~Scene();

    // Entity& GetEntityByUUID(UUID entity_ID);
    std::vector<Entity> Query(std::function<bool(Entity& entity)> predicate);

};

}