#include "Entity.h"

namespace Saddle {
    
Entity::Entity() { }

Entity::Entity(Scene& scene) : m_Scene(&scene) { }

std::vector<Entity*> Entity::QueryScene(std::function<bool(const Entity& entity)> predicate)
{
    return m_Scene->Query(predicate);
}

}