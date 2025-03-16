#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include "physics/collision.hpp"
#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

namespace phe::physics::collision {

void resolveCollision(RigidBody &a, RigidBody &b, CollisionInfo collisionInfo) {
    auto mpa = collisionInfo.mpa;
    auto penetrationDepth = collisionInfo.penetrationDepth;

    auto contactPointA = findContactPoint(a, mpa, penetrationDepth);
    auto contactPointB = findContactPoint(b, -mpa, penetrationDepth);

    auto rA = contactPointA - a.trans.translation;
    auto rB = contactPointB - b.trans.translation;

    glm::vec3 vA = a.linearVel + (glm::cross(a.angularVel, rA));
    glm::vec3 vB = b.linearVel + (glm::cross(b.angularVel, rB));

    glm::mat3 invertedInertiaTensorA = glm::inverse(a.inertiaTensor);
    glm::mat3 invertedInertiaTensorB = glm::inverse(b.inertiaTensor);

    glm::vec3 relativeVel = vA - vB;
    float j = -(1 + RESTITUTION_CO) * glm::dot(relativeVel, mpa) /
        (
          (1.0f / a.mass) +
          (1.0f / b.mass) +
          glm::dot(glm::cross(rA, mpa), invertedInertiaTensorA * glm::cross(rA, mpa)) +
          glm::dot(glm::cross(rB, mpa), invertedInertiaTensorB * glm::cross(rB, mpa))
        );

    glm::vec3 impulse = j * mpa;

    physics::applyImpulse(a, impulse, rA);
    physics::applyImpulse(b, -impulse, rB);
}

} // namespace phe::physics::collision

