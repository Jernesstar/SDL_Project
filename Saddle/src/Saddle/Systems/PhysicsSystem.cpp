#include "PhysicsSystem.h"

#include <cmath>

#include "Saddle/Core/Assert.h"

// Note: Maybe move these into the PhysicsSystem itself
#define Pi 3.1415926535897932384626433f
#define DEGREES_TO_RADIANS(degrees) degrees * (Pi / 180.0f)

namespace Saddle {

void PhysicsSystem::SetGravity(float gravity) { Gravity = gravity; }

void PhysicsSystem::ApplyForce(Entity& entity, float force, float angle)
{
    SADDLE_CORE_ASSERT(HasDependencies(entity));
    
    auto [rigidbody, _] = GetDependencies(entity);

    float radians = DEGREES_TO_RADIANS(angle);
    float sine = std::sin(radians);
    float cosine = std::cos(radians);

    // Since sin^2(theta) + cos^2(theta) = 1, these values can be used to divide up 
    // the amount of force to apply to the entity on both axes
    float x_ratio = cosine * cosine, y_ratio = sine * sine;
    
    // If the angle of the incoming force is in the right half of the unit circle, 
    // we want the resulting ratio to be negative and push the entity to the left
    if(cosine > 0.0f) x_ratio *= -1;

    // If the angle of the incoming force is in the bottom half of the unit circle,
    // we want the result ratio to be negative and push the entity up
    if(sine < 0.0f) y_ratio *= -1;

    rigidbody->Velocity += Vector2D{ x_ratio, y_ratio } * force;
    rigidbody->Speed = rigidbody->Velocity.Magnitude();
}

void PhysicsSystem::Update(Entity& entity, TimeStep ts)
{
    SADDLE_CORE_ASSERT(HasDependencies(entity));

    auto [rigidbody, transform] = GetDependencies(entity);
    
    // velocity = delta(position) / delta(time) =>
    // delta(position) = velocity * delta(time)
    transform->Coordinate += rigidbody->Velocity * ts;
    transform->Rotation += rigidbody->RotationSpeed * ts;
}

}