#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

namespace phe::math {
    struct Transform {
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::quat rotation    = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 scale       = glm::vec3(1.0f, 1.0f, 1.0f);
    };

    glm::mat4 toMatrix(const Transform& t);
}

