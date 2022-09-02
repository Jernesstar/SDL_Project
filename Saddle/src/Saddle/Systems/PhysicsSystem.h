#pragma once

#include "Saddle/Core/TimeStep.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {

class PhysicsSystem {
public:
    static void SetGravity(float gravity);
    static void ApplyForce(Entity& entity, float force, float angle);
    static void Update(Entity& entity, TimeStep ts);

private:
    static float Gravity;

private:
    PhysicsSystem() = delete;
    ~PhysicsSystem() = delete;
};
}