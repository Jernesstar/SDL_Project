#pragma once

#include <set>
#include <functional>

#include "Saddle/Core/Time.h"
#include "Saddle/Core/UUID.h"
#include "Saddle/ECS/Registry.h"

namespace Saddle {

class Entity;

class Scene {
public:
    Scene() : m_LastFrameTime(Time::GetTime()) { };
    ~Scene() = default;

    void AddEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

    Entity& GetEntityByUUID(UUID entity_id);

    void Update();
    void Render();
    void Pause();

private:
    Registry m_Registry;
    TimePoint m_LastFrameTime;

    friend class Entity;
};

}