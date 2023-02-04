#pragma once

#include <unordered_map>

#include "Components.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

class Entity;

class ComponentManager {
public:
    ComponentManager() { }
    ~ComponentManager() = default;

    template<typename TComponent>
    bool HasComponent(Entity* entity)
    {
        if(GetComponents<TComponent>().count(entity))
            return true;

        return false;
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Entity* entity, Args&&... args)
    {
        if(HasComponent<TComponent>(entity))
            SADDLE_CORE_LOG_WARNING("AddComponent(): Entity already has component"); 
        else
            GetComponents<TComponent>().try_emplace(entity, std::forward<Args>(args)...);

        return GetComponents<TComponent>()[entity]; 
    }

    template<typename TComponent>
    TComponent& GetComponent(Entity* entity)
    {
        SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity),
            "GetComponent(): Entity does not have component");

        return GetComponents<TComponent>()[entity];
    }

    template<typename TComponent>
    void RemoveComponent(Entity* entity)
    {
        if(!HasComponent<TComponent>(entity))
            SADDLE_CORE_LOG_WARNING("RemoveComponent(): Entity does not have component");
        else
            GetComponents<TComponent>().erase(entity);
    }

private:
    std::unordered_map<Entity*, EventListenerComponent> EventListenerComponents;
    std::unordered_map<Entity*, TagComponent> TagComponents;
    std::unordered_map<Entity*, TextureComponent> TextureComponents;
    std::unordered_map<Entity*, TransformComponent> TransformComponents;

private:
    template<typename TComponent>
    std::unordered_map<Entity*, TComponent>& GetComponents();

    friend class Registry;
};

}

