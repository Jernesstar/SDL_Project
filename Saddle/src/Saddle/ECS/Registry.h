#pragma once

#include <set>
#include <unordered_map>

#include "ComponentManager.h"

namespace Saddle {

class Entity;

class Registry {
public:
    Registry() : m_Entities() { }
    ~Registry() = default;

    void AddEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

    std::set<Entity*> GetAllEntities() { return m_Entities; };

    template<typename TComponent>
    std::set<Entity*> GetAllEntitiesWith();

private:
    std::set<Entity*> m_Entities;
};

}