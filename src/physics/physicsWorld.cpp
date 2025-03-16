#include "physics/physicsWorld.hpp"
#include "graphics/renderer.hpp"
#include "physics/collision.hpp"
#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"
#include <cstddef>

namespace phe::physics {

void PhysicsWorld::update(float dt, graphics::Renderer& r) {
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i+1; j < bodies.size(); j++) {
            auto& b1 = bodies[i];
            auto& b2 = bodies[j];
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

