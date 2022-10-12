#include "ComponentManager.h"

#include <utility>

#define SELECT_MAP(TComponent) \
template<> \
std::unordered_map<Entity*, TComponent>& ComponentManager::SelectComponents<TComponent>() \
{ \
    return TComponent##s; \
}

namespace Saddle {

SELECT_MAP(EventListenerComponent);
SELECT_MAP(RigidBodyComponent);
SELECT_MAP(RGBColorComponent);
SELECT_MAP(TextureComponent);
SELECT_MAP(TransformComponent);

}