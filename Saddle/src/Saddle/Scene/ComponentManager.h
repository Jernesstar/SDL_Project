#pragma once

#include <unordered_map>

#include "Components.h"
#include "Entity.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

class ComponentManager {
public:
    ComponentManager() { }
    ~ComponentManager() = default;

    template<typename TComponent>
    bool HasComponent(Entity& entity)
    {
        if(SelectComponents<TComponent>().count(&entity))
            return true;
    
        return false;
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Entity& entity, Args&&... args)
    {
        SADDLE_CORE_ASSERT_ARGS(!HasComponent<TComponent>(entity), "AddComponent(): Entity already has component"); 

        SelectComponents<TComponent>().try_emplace(&entity, std::forward(args)...); 
        return SelectComponents<TComponent>()[&entity]; 
    }

    template<typename TComponent>
    TComponent& GetComponent(Entity& entity)
    {
        SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity),
            "GetComponent(): Entity does not have component");
    
        return SelectComponents<TComponent>()[&entity];
    }

    template<typename TComponent>
    void RemoveComponent(Entity& entity)
    {
        SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity), "RemoveComponent(): Entity does not have component");

        SelectComponents<TComponent>().erase(&entity);
    }

private:
    std::unordered_map<Entity*, EventListenerComponent> EventListenerComponents;
    std::unordered_map<Entity*, RigidBodyComponent> RigidBodyComponents;
    std::unordered_map<Entity*, RGBColorComponent> RGBColorComponents;
    std::unordered_map<Entity*, TextureComponent> TextureComponents;
    std::unordered_map<Entity*, TransformComponent> TransformComponents;

private:
    template<typename TComponent>
    std::unordered_map<Entity*, TComponent>& SelectComponents();
};

}

