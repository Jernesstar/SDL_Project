#pragma once

#include <unordered_map>
#include <typeinfo>
#include <utility>

#include "Components.h"

namespace Saddle {

class Entity {

public:
    Entity() : m_Components() {}
    ~Entity() = default;

    template<typename Component>
    bool HasComponent();

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args);

    template<typename Component>
    void RemoveComponent();
    
    template<typename Component>
    Component& GetComponent();

private:
    std::unordered_map<std::size_t, IComponent*> m_Components;

};

}