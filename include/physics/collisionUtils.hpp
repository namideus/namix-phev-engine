#include <glm/glm.hpp>

#include "physics/rigidbody.hpp"

namespace phe::physics::collision {

/**
 * The parameter rb NEEDS to have a cube mesh.
 *
 * @return vector of face normals for a cube.
 */
const std::vector<glm::vec3> computeCubeNormals(const RigidBody& rb);
const std::vector<glm::vec3> computeCubeEdges(const RigidBody& rb);

bool areOverlapping(const RigidBody& a, const RigidBody& b);

} // namespace phe::physics::collision

