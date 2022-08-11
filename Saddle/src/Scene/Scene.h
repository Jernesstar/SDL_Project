#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace Saddle {

class Entity;

class Scene {

public:
    Scene();
    ~Scene();

    // Entity& GetEntityByUUID(UUID entity_ID);

    std::vector<Entity*> Query(std::function<bool(const Entity& entity)> predicate);

private:
    std::unordered_map<int, Entity*> entities;

};

}