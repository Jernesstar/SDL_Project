#pragma once

#include "ComponentManager.h"
#include "Scene.h"

namespace Saddle {

class Entity {

public:
    Entity();
    Entity(Scene& scene);
    ~Entity() = default;

    std::vector<Entity*> QueryScene(std::function<bool(const Entity& entity)> predicate);
    void OnUpdate(TimeStep ts);

    template<typename Component>
    bool HasComponent()
    {
        return m_Components.HasComponent<Component>();
    }

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args)
    {
        return m_Components.AddComponent<Component>(args...);
    }

    template<typename Component>
    void RemoveComponent()
    {
        m_Components.RemoveComponent<Component>();
    }
    
    template<typename Component>
    Component& GetComponent()
    {
        return m_Components.GetComponent<Component>();
    }

private:
    ComponentManager m_Components;
    Scene* m_Scene = nullptr;

};

}