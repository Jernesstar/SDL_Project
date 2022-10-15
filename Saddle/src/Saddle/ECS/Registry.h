#pragma once

#include <set>
#include <unordered_map>

#include "ComponentManager.h"

namespace Saddle {

class Entity;

class Registry {
public:
    Registry() : m_ComponentManager() { }
    ~Registry() = default;

    void AddEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

    std::set<Entity*> GetAllEntities();

    template<typename TComponent>
    std::set<Entity*> GetAllEntitiesWith();

    ComponentManager& GetComponentManager() { return m_ComponentManager; }

private:
    ComponentManager m_ComponentManager;
};

}