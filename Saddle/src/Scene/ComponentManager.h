#pragma once

#include <unordered_map>
#include <typeinfo>
#include <utility>

#include "Components.h"
#include "Assert.h"

namespace Saddle {

class ComponentManager {
public:
    ComponentManager() : m_Components() { }
    ~ComponentManager() = default;

    template<typename Component>
    bool HasComponent()
    {
        if(m_Components.find(Hash<Component>()) == m_Components.end())
            return false;

        return true;
    }

    template<typename Component, typename... Args>
    Component& AddComponent(Args&&... args)
    {
        SADDLE_CORE_ASSERT(!HasComponent<Component>(), "Entity already has component '" + std::string(typeid(Component).name()) + "'");

        Component* component = new Component(std::forward<Args>(args)...);
        m_Components[Hash<Component>()] = component;
        return *component;
    }

    template<typename Component>
    void RemoveComponent()
    {
        SADDLE_CORE_ASSERT(HasComponent<Component>(), "Entity does not have component '" + std::string(typeid(Component).name()) + "'");

        m_Components.erase(Hash<Component>());
    }
    
    template<typename Component>
    Component& GetComponent()
    {
        SADDLE_CORE_ASSERT(HasComponent<Component>(), "Entity does not have component '" + std::string(typeid(Component).name()) + "'");
        
        return *(Component*)m_Components[Hash<Component>()];
    }

private:
    std::unordered_map<std::size_t, IComponent*> m_Components;

private:
    template<typename Component>
    std::size_t Hash()
    {
        return typeid(Component).hash_code();
    }
};

}