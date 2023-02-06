#pragma once

#include "Scene.h"

namespace Saddle {

class Entity {
public:
    Entity(Scene& scene) : m_Scene(&scene) { }
    ~Entity() { m_Scene->RemoveEntity(*this); }

    template<typename TComponent>
    bool HasComponent()
    {
        return m_Scene->m_Registry.GetComponentManager().HasComponent<TComponent>(this);
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Args&&... args)
    {
        return m_Scene->m_Registry.GetComponentManager().AddComponent<TComponent>(this, args...);
    }

    template<typename TComponent>
    void RemoveComponent()
    {
        m_Scene->m_Registry.GetComponentManager().RemoveComponent<TComponent>(this);
    }
    
    template<typename TComponent>
    TComponent& GetComponent()
    {
        return m_Scene->m_Registry.GetComponentManager().GetComponent<TComponent>(this);
    }

private:
    Scene* m_Scene = nullptr;

    friend class Scene;
};

}