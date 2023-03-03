#include "Registry.h"

namespace Saddle {

void Registry::AddEntity(Entity& entity)
{
    if(m_Entities.find(&entity) != m_Entities.end())
        return;
    m_Entities.insert(&entity);
}

void Registry::RemoveEntity(Entity& entity)
{
    if(m_Entities.find(&entity) == m_Entities.end())
        return;
    m_Entities.erase(&entity);
}

}