#include <cstddef>

#include "physics/physicsWorld.hpp"
#include "graphics/renderer.hpp"
#include "physics/collision.hpp"
#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

namespace phe::physics {

PhysicsWorld::PhysicsWorld() {
    gp.gridSize = 10.0f;
    gp.gridCells.clear();
}

void PhysicsWorld::update(float dt, graphics::Renderer& r) {
    auto filteredBodies = collision::broadPhaseFilter(bodies, gp);

    for (size_t i = 0; i < filteredBodies.size(); i++) {
        for (size_t j = i+1; j < filteredBodies.size(); j++) {
            auto& b1 = filteredBodies[i];
            auto& b2 = filteredBodies[j];
            auto info = collision::areColliding(*b1, *b2);
            if (info.isColliding) {
                collision::resolveCollision(*b1, *b2, info);
            }
        }
    }

    for (auto& b : bodies) {
        graphics::drawRigidBody(*b, r);

        if (b->isDynamic) {
            applyForce(*b, GRAVITY, glm::vec3(0.0f, 0.0f, 0.0f));
            integrateForces(*b, dt);
            integrateVelocity(*b, dt);
        }
    }
}

void PhysicsWorld::addRigidBody(RigidBody* rb) {
    bodies.push_back(rb);
}

}

