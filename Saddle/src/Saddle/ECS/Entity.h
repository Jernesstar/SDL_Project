#pragma once

#include "Scene.h"
#include "ComponentManager.h"

namespace Saddle {

class Entity {
public:
    Entity() : m_Scene(nullptr) { }
    Entity(Scene& scene) : m_Scene(&scene) { }
    ~Entity() { if(m_Scene) m_Scene->RemoveEntity(*this); }

    template<typename TComponent>
    bool HasComponent()
    {
        return m_ComponentManager.HasComponent<TComponent>(this);
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Args&&... args)
    {
        return m_ComponentManager.AddComponent<TComponent>(this, args...);
    }

    template<typename TComponent>
    void RemoveComponent()
    {
        m_ComponentManager.RemoveComponent<TComponent>(this);
    }
    
    template<typename TComponent>
    TComponent& GetComponent()
    {
        return m_ComponentManager.GetComponent<TComponent>(this);
    }

private:
    Scene* m_Scene = nullptr;
    ComponentManager m_ComponentManager;

    friend class Scene;
};

}