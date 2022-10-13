#pragma once

#include <set>
#include <unordered_map>

#include "ComponentManager.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {

class Registry {
public:
    Registry() : m_ComponentManager() { }
    ~Registry();

    void AddEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

    std::set<Entity*> GetAllEntities()
    {
    }

    template<typename TComponent>
    std::set<Entity*> GetAllEntitiesWith()
    {
        auto& map = m_ComponentManager.GetComponents<TComponent>();
        std::set<Entity*> result;
        
        for(auto& [entity_ptr, _] : map)
            result.emplace(entity_ptr);

        return result;
    }

    template<typename TComponent>
    std::set<TComponent*> GetComponents()
    {
        return m_ComponentManager.GetComponents<TComponent>();
    }

private:
    ComponentManager m_ComponentManager;
};

}