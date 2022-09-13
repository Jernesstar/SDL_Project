#pragma once

#include "Saddle/Core/Time.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {

struct PhysicsSystemDependencies {
    RigidBodyComponent* rigidbody_component;
    TransformComponent* transform_component;
};

class PhysicsSystem {
public:
    static void SetGravity(float gravity);
    static void ApplyForce(Entity& entity, float force, float angle);
    static void Update(Entity& entity, TimeStep ts);

    static bool HasDependencies(Entity& entity)
    {
        return entity.HasComponent<RigidBodyComponent>() && entity.HasComponent<TransformComponent>();
    }
    
private:
    inline static float Gravity = 0;

private:
    PhysicsSystem() = delete;
    ~PhysicsSystem() = delete;

    static PhysicsSystemDependencies GetDependencies(Entity& entity)
    {
        return { &entity.GetComponent<RigidBodyComponent>(), &entity.GetComponent<TransformComponent>() };
    }
};

}