#ifndef COLLISION_H
#define COLLISION_H

#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

#define RESTITUTION_CO 0.78f

namespace phe::physics::collision {

void resolveCollision(RigidBody& a, RigidBody& b, CollisionInfo collisionInfo);

} // namespace phe::physics::collision

#endif

