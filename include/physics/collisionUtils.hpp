#include <glm/glm.hpp>

#include "physics/rigidbody.hpp"

namespace phe::physics::collision {

/**
 * The parameter rb NEEDS to have a cube mesh.
 *
 * @return vector of face normals for a cube.
 */
std::vector<glm::vec3> computeCubeNormals(const RigidBody& rb);
std::vector<glm::vec3> computeCubeEdges(const RigidBody& rb);

bool areColliding(RigidBody& a, RigidBody& b);

float projectOntoAxis(const glm::vec3& vertex, const glm::vec3& axis);

} // namespace phe::physics::collision

