#include "PhysicsSystem.h"

#include "Saddle/Core/Assert.h"

namespace Saddle {

void PhysicsSystem::SetGravity(float gravity) { Gravity = gravity; }

void PhysicsSystem::ApplyForce(Entity& entity, float force, float angle)
{
    SADDLE_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>())
    SADDLE_CORE_ASSERT(angle < 360.0f, "Incorrect angle");

    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    
    // -(1- proportion): this will calculate the velocity on the x-axis
    // This is negated so as to have x velocity to the left be negative

    if(angle <= 180.0f)
    {
        float proportion = angle / 90.0f;
        rigidbody.VelocityX += force * -(1 - proportion);
        rigidbody.VelocityY += force * proportion;
    }
    else if(angle > 180.0f)
    {
        float proportion = angle / 270.0f;
        rigidbody.VelocityX += force * -(1 - proportion);
        rigidbody.VelocityY += force * proportion;
    }
}

}