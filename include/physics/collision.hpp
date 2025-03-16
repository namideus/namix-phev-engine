#ifndef COLLISION_H
#define COLLISION_H

#include <tuple>
#include <unordered_map>

#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

#define RESTITUTION_CO 0.78f

namespace phe::physics::collision {

struct GridPartition {
    // Grid position, grid's owned bodies
    std::unordered_map<std::tuple<int, int, int>, std::vector<RigidBody*>> gridCells;
    float gridSize;
};

void resolveCollision(RigidBody& a, RigidBody& b, CollisionInfo collisionInfo);

/**
 * This function returns a vector of rigid bodies that COULD collide,
 * significantly reducing the amount of calculations needed, by only returning
 * the bodies that are closest to each other.
 */
std::vector<RigidBody*> broadPhaseFilter(std::vector<RigidBody*> bodies, GridPartition gp);

} // namespace phe::physics::collision

#endif

