#pragma once

#include <unordered_map>

#include "Components.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

class Entity;

class ComponentManager {
public:
    ComponentManager() { }
    ~ComponentManager() = default;

    template<typename TComponent>
    bool HasComponent(Entity* entity)
    {
        if(GetComponents<TComponent>().count(entity))
            return true;

        return false;
    }

    template<typename TComponent, typename... Args>
    TComponent& AddComponent(Entity* entity, Args&&... args)
    {
        if(HasComponent<TComponent>(entity))
            SADDLE_CORE_LOG_WARNING("AddComponent(): Entity already has %s", TypeName<TComponent>::GetName()); 
        else
            GetComponents<TComponent>().try_emplace(entity, std::forward<Args>(args)...);

        return GetComponents<TComponent>()[entity]; 
    }

    template<typename TComponent>
    TComponent& GetComponent(Entity* entity)
    {
        SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity),
            "GetComponent(): Entity does not have %s", TypeName<TComponent>::GetName());

        return GetComponents<TComponent>()[entity];
    }

    template<typename TComponent>
    void RemoveComponent(Entity* entity)
    {
        if(!HasComponent<TComponent>(entity))
            SADDLE_CORE_LOG_WARNING("RemoveComponent(): Entity does not have %s", TypeName<TComponent>::GetName());
        else
            GetComponents<TComponent>().erase(entity);
    }

private:
    std::unordered_map<Entity*, EventListenerComponent> EventListenerComponents;
    std::unordered_map<Entity*, TagComponent> TagComponents;
    std::unordered_map<Entity*, TextureComponent> TextureComponents;
    std::unordered_map<Entity*, TransformComponent> TransformComponents;

private:
    template<typename TComponent>
    std::unordered_map<Entity*, TComponent>& GetComponents();

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

