#include "ComponentManager.h"

#include <utility>

#define GET_COMPONENTS(TComponent) \
template<> \
std::unordered_map<Entity*, TComponent>& ComponentManager::GetComponents<TComponent>() \
{ \
    return TComponent##s; \
}

namespace Saddle {

GET_COMPONENTS(EventListenerComponent);
GET_COMPONENTS(RigidBodyComponent);
GET_COMPONENTS(RGBColorComponent);
GET_COMPONENTS(TextureComponent);
GET_COMPONENTS(TransformComponent);

}