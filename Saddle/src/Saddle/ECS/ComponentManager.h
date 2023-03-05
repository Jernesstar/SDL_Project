#pragma once

#include <vector>

#include "Components.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

class Entity;

class ComponentManager {
public:
    ComponentManager() = default;
    ~ComponentManager() = default;

    template<typename TComponent>
    bool HasComponent()
    {
        if(GetComponents<TComponent>().size() != 0)
            return true;

        return false;
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Entity* entity, Args&&... args)
    {
        if(HasComponent<TComponent>())
            SADDLE_CORE_LOG_WARNING("AddComponent(): Entity already has %s", TypeName<TComponent>::GetName()); 
        else
            GetComponents<TComponent>().emplace_back(std::forward<Args>(args)...);

        return GetComponents<TComponent>()[0];
    }

    template<typename TComponent>
    TComponent& GetComponent(Entity* entity)
    {
        SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(),
            "GetComponent(): Entity does not have %s", TypeName<TComponent>::GetName());

        return GetComponents<TComponent>()[0];
    }

    template<typename TComponent>
    void RemoveComponent(Entity* entity)
    {
        if(!HasComponent<TComponent>())
            SADDLE_CORE_LOG_WARNING("RemoveComponent(): Entity does not have %s", TypeName<TComponent>::GetName());
        else
            GetComponents<TComponent>().erase(GetComponents<TComponent>().begin());
    }

private:
    std::vector<EventListenerComponent> EventListenerComponents;
    std::vector<TagComponent> TagComponents;
    std::vector<TextureComponent> TextureComponents;
    std::vector<TransformComponent> TransformComponents;

private:
    template<typename TComponent>
    std::vector<TComponent>& GetComponents();

    template<typename TComponent>
    struct TypeName
    {
        static const char* GetName() { return ""; }
    };

    friend class Registry;
};

template<>
struct ComponentManager::TypeName<EventListenerComponent> { static const char* GetName() { return "EventListenerComponent"; } };

template<>
struct ComponentManager::TypeName<TagComponent> { static const char* GetName() { return "TagComponent"; } };

template<>
struct ComponentManager::TypeName<TextureComponent> { static const char* GetName() { return "TextureComponent"; } };

template<>
struct ComponentManager::TypeName<TransformComponent> { static const char* GetName() { return "TransformComponent"; } };

}

