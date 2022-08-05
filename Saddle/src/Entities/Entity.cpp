#include "Entity.h"

namespace Saddle {

    template<typename T>
    bool Entity::HasComponent()
    {
        if(m_Components.find(typeid(T).hash_code()) == m_Components.end())
            return false;

        return true;
    }

    template<typename T, typename... Args>
    T& Entity::AddComponent(Args&&... args)
    {
        T* component = nullptr;
        if(!HasComponent<T>())
        {
            component = new T(std::forward<Args>(args)...);
            m_Components[typeid(T).hash_code()] = component;
        }

        return *component;
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        if(HasComponent<T>())
            m_Components.erase(typeid(T).hash_code());
    }

    template<typename T>
    T& Entity::GetComponent()
    {
        if(HasComponent<T>())
            return *m_Components[typeid(T).hash_code()];
            
        return *(T*)nullptr;
    }
    
}