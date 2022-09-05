#include "PhysicsSystem.h"

#include "Saddle/Core/Assert.h"

namespace Saddle {

void PhysicsSystem::SetGravity(float gravity) { Gravity = gravity; }

void PhysicsSystem::ApplyForce(Entity& entity, float force, float angle)
{
    SADDLE_CORE_ASSERT(HasDependencies(entity));
}

void PhysicsSystem::Update(Entity& entity, TimeStep ts)
{
    SADDLE_CORE_ASSERT(HasDependencies(entity));

    auto [rigidbody, transform] = GetDependencies(entity);
    
    transform->Coordinate += rigidbody->Velocity * ts;
    transform->Rotation += rigidbody->RotationSpeed * ts;
}

}