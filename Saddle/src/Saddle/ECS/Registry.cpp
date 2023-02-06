#include "Registry.h"

namespace Saddle {

void Registry::RemoveEntity(Entity& entity)
{
    if(m_ComponentManager.HasComponent<EventListenerComponent>(&entity))
        m_ComponentManager.RemoveComponent<EventListenerComponent>(&entity);
    if(m_ComponentManager.HasComponent<TagComponent>(&entity))
        m_ComponentManager.RemoveComponent<TagComponent>(&entity);
    if(m_ComponentManager.HasComponent<TextureComponent>(&entity))
        m_ComponentManager.RemoveComponent<TextureComponent>(&entity);
    if(m_ComponentManager.HasComponent<TransformComponent>(&entity))
        m_ComponentManager.RemoveComponent<TransformComponent>(&entity);
}

}