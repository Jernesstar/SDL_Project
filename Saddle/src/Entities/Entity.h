#pragma once

#include "ComponentManager.h"

namespace Saddle {

class Entity {

public:
    Entity();
    ~Entity() = default;

    template<typename Component>
    bool HasComponent()
    {
        return components.HasComponent<Component>();
    }

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args)
    {
        return components.AddComponent<Component>(args...);
    }

    template<typename Component>
    void RemoveComponent()
    {
        components.RemoveComponent<Component>();
    }
    
    template<typename Component>
    Component& GetComponent()
    {
        return components.GetComponent<Component>();
    }

private:
    ComponentManager components;

};

}