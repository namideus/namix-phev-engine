#include "physics/rigidbody.hpp"

namespace phe::physics {

RigidBody::RigidBody(float r, float g, float b) {
    mesh = graphics::createCubeMesh(r, g, b);
}

RigidBody::~RigidBody() {
    graphics::destroyMesh(mesh);
}

void setPosition(RigidBody& rb, float x, float y, float z) {
    rb.trans.translation.x = x;
    rb.trans.translation.y = y;
    rb.trans.translation.z = z;
}

void setPosition(RigidBody& rb, glm::vec3 newPosition) {
    rb.trans.translation = newPosition; 
}

} // namespace phe::physics

