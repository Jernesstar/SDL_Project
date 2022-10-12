#include "ComponentManager.h"

#include <utility>

#define HAS_COMPONENT(TComponent) \
template<> \
bool ComponentManager::HasComponent<TComponent>(Entity& entity) \
{ \
    if(TComponent##s.count(&entity)) \
        return true; \
\
    return false; \
}

#define GET_COMPONENT(TComponent) \
template<> \
TComponent& ComponentManager::GetComponent<TComponent>(Entity& entity) \
{ \
    SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity), \
        "GetComponent(): Entity does not have component"); \
 \
    return TComponent##s[&entity]; \
}

#define REMOVE_COMPONENT(TComponent) \
template<> \
void ComponentManager::RemoveComponent<TComponent>(Entity& entity) \
{ \
    SADDLE_CORE_ASSERT_ARGS(HasComponent<TComponent>(entity), "RemoveComponent(): Entity does not have component"); \
 \
    TComponent##s.erase(&entity); \
}

#define ADD_TO_COMPONENT_MANAGER(TComponent) \
HAS_COMPONENT(TComponent); \
GET_COMPONENT(TComponent); \
REMOVE_COMPONENT(TComponent);

namespace Saddle {

ADD_TO_COMPONENT_MANAGER(EventListenerComponent);
ADD_TO_COMPONENT_MANAGER(RigidBodyComponent);
ADD_TO_COMPONENT_MANAGER(RGBColorComponent);
ADD_TO_COMPONENT_MANAGER(TextureComponent);
ADD_TO_COMPONENT_MANAGER(TransformComponent);

}