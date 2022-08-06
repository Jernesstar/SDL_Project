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
    bool HasComponent()
    {
        if(m_Components.find(typeid(Component).hash_code()) == m_Components.end())
            return false;

        return true;
    }

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args)
    {
        if(!HasComponent<Component>())
        {
            Component* component = new Component(std::forward<Args>(args)...);
            m_Components[typeid(Component).hash_code()] = component;
            return *component;
        }
        return *(Component*)nullptr;
    }

    template<typename Component>
    void RemoveComponent()
    {
        if(HasComponent<Component>())
            m_Components.erase(typeid(Component).hash_code());
    }
    
    template<typename Component>
    Component& GetComponent()
    {
        if(HasComponent<Component>())
            return *(Component*)m_Components[typeid(Component).hash_code()];
            
        return *(Component*)nullptr;
    }

private:
    std::unordered_map<std::size_t, IComponent*> m_Components;

};

}