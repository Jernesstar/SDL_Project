#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "TimeStep.h"

namespace Saddle {

class Entity;

class Scene {
public:
    Scene();
    ~Scene();

    // Entity& GetEntityByUUID(UUID entity_ID);
    
    void OnUpdate();
    void OnSceneRender();

    void AddEntity(Entity& entity);

    std::vector<Entity*> Query(std::function<bool(const Entity& entity)> predicate);

private:
    std::vector<Entity*> entities;
    float m_LastFrameTime;
};

}