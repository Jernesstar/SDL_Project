#pragma once

#include <unordered_map>

#include "Components.h"
#include "Entity.h"
#include "Saddle/Core/Assert.h"

#define ADD_COMPONENT(TComponent) \
template<typename... Args> \
TComponent& AddComponent(Entity& entity, Args&&... args) \
{ \
    SADDLE_CORE_ASSERT_ARGS(!HasComponent<TComponent>(), "AddComponent(): Entity already has component '", TComponent, "'"); \
 \
    TComponent##s.emplace(&entity, std::forward(args)...); \
    return TComponent##s[&entity]; \
}

namespace Saddle {

class ComponentManager {
public:
    ComponentManager() { }
    ~ComponentManager() = default;

    template<typename Component>
    bool HasComponent(Entity& entity);

    // ADD_COMPONENT(EventListenerComponent);
    // ADD_COMPONENT(RigidBodyComponent);
    // ADD_COMPONENT(RGBColorComponent);
    // ADD_COMPONENT(TextureComponent);
    // ADD_COMPONENT(TransformComponent);

    template<typename TComponent>
    TComponent& GetComponent(Entity& entity);

    template<typename TComponent>
    void RemoveComponent(Entity& entity);

private:
    std::unordered_map<Entity*, EventListenerComponent> EventListenerComponents;
    std::unordered_map<Entity*, RigidBodyComponent> RigidBodyComponents;
    std::unordered_map<Entity*, RGBColorComponent> RGBColorComponents;
    std::unordered_map<Entity*, TextureComponent> TextureComponents;
    std::unordered_map<Entity*, TransformComponent> TransformComponents;
};

}