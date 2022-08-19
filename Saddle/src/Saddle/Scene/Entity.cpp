#include "Entity.h"

namespace Saddle {
    
Entity::Entity() : m_Components() { }

Entity::Entity(Scene& scene) : m_Components(), m_Scene(&scene) { }

std::vector<Entity*> Entity::QueryScene(std::function<bool(const Entity& entity)> predicate)
{
    return m_Scene->Query(predicate);
}

}