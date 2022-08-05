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

    template<typename T>
    bool HasComponent();

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    void RemoveComponent();
    
    template<typename T>
    T& GetComponent();

private:
    std::unordered_map<std::size_t, IComponent*> m_Components;

};

}