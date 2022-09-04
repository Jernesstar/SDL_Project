#include "PhysicsSystem.h"

#include "Saddle/Core/Assert.h"

namespace Saddle {

PhysicsSystemDependencies PhysicsSystem::GetDependencies(Entity& entity)
{
    return { &entity.GetComponent<RigidBodyComponent>(), &entity.GetComponent<TransformComponent>() };
}

void PhysicsSystem::SetGravity(float gravity) { Gravity = gravity; }

void PhysicsSystem::ApplyForce(Entity& entity, float force, float angle)
{
    SADDLE_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>())
    SADDLE_CORE_ASSERT(angle < 360.0f, "Incorrect angle");
}

void PhysicsSystem::Update(Entity& entity, TimeStep ts)
{
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    auto& transform = entity.GetComponent<TransformComponent>();
    
    transform.Coordinate += rigidbody.Velocity * ts;
    transform.Rotation += rigidbody.RotationSpeed * ts;
}

}