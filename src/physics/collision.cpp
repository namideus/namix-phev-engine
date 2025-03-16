#include <cmath>
#include <glm/glm.hpp>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "physics/collision.hpp"
#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

namespace phe::physics::collision {

static std::tuple<int, int, int> findBodyGridCell(RigidBody* b, GridPartition& gp) {
    int gridX = (int)floor(b->trans.translation.x / gp.gridSize);
    int gridY = (int)floor(b->trans.translation.y / gp.gridSize);
    int gridZ = (int)floor(b->trans.translation.z / gp.gridSize);

    return std::make_tuple(gridX, gridY, gridZ);
}

/**
 * @param cell The cell you want to check the neighbors of.
 * @param out The output vector that is going to have all of the rigid bodies of the neighboring cells
 */
static void checkNeighboringCells(std::tuple<int, int, int> cell, RigidBody* currBody, GridPartition& gp, std::vector<RigidBody*>& out) {
    std::unordered_set<RigidBody*> addedBodies;

    // Go over every neighbor of the current cell in a 3x3x3 grid
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            for (int z = -1; z <= 1; ++z) {
                
                // Skip our current cell.
                if (x == 0 && y == 0 && z == 0) continue;

                // Get the neighbor cell by adding current cell coordinates + current neighbor coordinates (represented by x, y and z)
                auto neighborCell = std::make_tuple(std::get<0>(cell) + x,
                                                    std::get<1>(cell) + y,
                                                    std::get<2>(cell) + z);

                // O(1) look up time
                auto it = gp.gridCells.find(neighborCell);
                if (it == gp.gridCells.end()) {
                    continue;
                }

                // Now add the bodies from neighbor cell to the output, ONLY IF
                // it's not found in addedBodies.
                for (RigidBody* neighborB : it->second) {
                    if (neighborB == currBody) continue;

                    auto itt = addedBodies.find(neighborB);
                    // If we DIDN'T find neighbor body in the addedBodies set,
                    // add it to the output.
                    if (itt == addedBodies.end()) {
                        out.push_back(neighborB);
                        addedBodies.insert(neighborB);
                    }
                }
            }
        }
    }
}

void resolveCollision(RigidBody &a, RigidBody &b, CollisionInfo collisionInfo) {
    glm::vec3 mpa = collisionInfo.mpa;
    float penetrationDepth = collisionInfo.penetrationDepth;

    glm::vec3 contactPointA = findContactPoint(a, mpa, penetrationDepth);
    glm::vec3 contactPointB = findContactPoint(b, -mpa, penetrationDepth);

    glm::vec3 rA = contactPointA - a.trans.translation;
    glm::vec3 rB = contactPointB - b.trans.translation;

    // Velocity of rigid body A
    glm::vec3 vA = a.linearVel + (glm::cross(a.angularVel, rA));

    // Velocity of rigid body B
    glm::vec3 vB = b.linearVel + (glm::cross(b.angularVel, rB));

    glm::mat3 invertedInertiaTensorA = glm::inverse(a.inertiaTensor);
    glm::mat3 invertedInertiaTensorB = glm::inverse(b.inertiaTensor);

    // We use relative velocity of both bodies to find the impulse needed
    // to push them apart. It's the reaction of the collision.
    glm::vec3 relativeVel = vA - vB;

    float j = -(1 + RESTITUTION_CO) * glm::dot(relativeVel, mpa) /
        (
          (1.0f / a.mass) +
          (1.0f / b.mass) +
          glm::dot(glm::cross(rA, mpa), invertedInertiaTensorA * glm::cross(rA, mpa)) +
          glm::dot(glm::cross(rB, mpa), invertedInertiaTensorB * glm::cross(rB, mpa))
        );

    // Impulse is given by j * n (Minimum Penetration Axis)
    glm::vec3 impulse = j * mpa;

    physics::applyImpulse(a, impulse, rA);
    physics::applyImpulse(b, -impulse, rB);
}

std::vector<RigidBody*> broadPhaseFilter(std::vector<RigidBody*> bodies, GridPartition& gp) {
    std::vector<RigidBody*> possibleCollisions;

    for (RigidBody* b : bodies) {
        std::tuple<int, int, int> cell = findBodyGridCell(b, gp);

        checkNeighboringCells(cell, b, gp, possibleCollisions);
    }

    return possibleCollisions;
}

} // namespace phe::physics::collision

