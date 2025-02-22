#include "ComponentManager.h"

#include <utility>

#define GET_COMPONENTS(TComponent) \
template<> \
std::vector<TComponent>& ComponentManager::GetComponents<TComponent>() \
{ \
    return TComponent##s; \
}

namespace Saddle {

GET_COMPONENTS(EventListenerComponent);
GET_COMPONENTS(TagComponent);
GET_COMPONENTS(TextureComponent);
GET_COMPONENTS(TransformComponent);

}