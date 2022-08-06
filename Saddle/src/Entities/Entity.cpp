#include "Entity.h"

namespace Saddle {

    template<typename Component>
    bool Entity::HasComponent()
    {
        if(m_Components.find(typeid(Component).hash_code()) == m_Components.end())
            return false;

        return true;
    }

    template<typename Component, typename... Args>
    Component& Entity::AddComponent(Args&&... args)
    {
        if(!HasComponent<Component>())
        {
            Component* component = new Component(std::forward<Args>(args)...);
            m_Components[typeid(Component).hash_code()] = component;
            return *component;
        }

        Component empty;
        return empty;
    }

    template<typename Component>
    void Entity::RemoveComponent()
    {
        if(HasComponent<Component>())
            m_Components.erase(typeid(Component).hash_code());
    }

    template<typename Component>
    Component& Entity::GetComponent()
    {
        if(HasComponent<Component>())
            return *m_Components[typeid(Component).hash_code()];
            
        Component empty;
        return empty;
    }
    
}