#pragma once

#include "Scene.h"

namespace Saddle {

class Entity {
public:
    Entity();
    Entity(Scene& scene);
    ~Entity() = default;

    std::vector<Entity*> QueryScene(std::function<bool(const Entity& entity)> predicate);

    template<typename Component>
    bool HasComponent()
    {
        ;
    }

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args)
    {
    }

    template<typename Component>
    void RemoveComponent()
    {
    }
    
    template<typename Component>
    Component& GetComponent()
    {
    }

private:
    Scene* m_Scene = nullptr;

    friend class Scene;
};

}