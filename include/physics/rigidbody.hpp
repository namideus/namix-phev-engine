#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <glm/glm.hpp>

#include "graphics/mesh.hpp"
#include "math_utils/transform.hpp"

namespace phe::physics {

struct RigidBody {
    math::Transform trans = math::Transform();

    glm::vec3 linearVel = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 linearAcc = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 angularVel = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 angularAcc = glm::vec3(0.0f, 0.0f, 0.0f);

    float mass = 1.0f;

    graphics::Mesh mesh;

    RigidBody(float r, float g, float b);
    ~RigidBody();
};

void applyLinearForce(RigidBody& rb);
void applyAngularForce(RigidBody& rb);

void setPosition(RigidBody& rb, float x, float y, float z);
void setPosition(RigidBody& rb, glm::vec3 newPosition);

}

#endif

