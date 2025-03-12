#include <glm/glm.hpp>

#include "graphics/mesh.hpp"
#include "math_utils/transform.hpp"

namespace phe::physics {
    struct RigidBody {
        math::Transform trans;

        glm::vec3 linearVel;
        glm::vec3 linearAcc;

        glm::vec3 angularVel;
        glm::vec3 angularAcc;

        float mass;

        graphics::Mesh mesh;
    };

    void applyLinearForce();
    void applyAngularForce();
}

