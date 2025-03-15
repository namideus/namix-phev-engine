#include "physics/collisionUtils.hpp"
#include "physics/rigidbody.hpp"

namespace phe::physics::collision {
    
const std::vector<glm::vec3> computeCubeNormals(const RigidBody &rb) {
    static const std::vector<glm::vec3> cubeLocalNormals = {
        // Normals for each face of the cube
        { 1,  0,  0},
        {-1,  0,  0},
        { 0,  1,  0},
        { 0, -1,  0},
        { 0,  0,  1},
        { 0,  0, -1}
    };

    std::vector<glm::vec3> worldNormals;
    worldNormals.reserve(cubeLocalNormals.size());

    for (const auto& normal : cubeLocalNormals) {
        worldNormals.push_back(rb.trans.rotation * normal);
    }

    return worldNormals;
}

const std::vector<glm::vec3> computeCubeEdges(const RigidBody& rb) {
    static const std::vector<glm::vec3> cubeLocalEdges = {
        {1, 0, 0}, // X axis
        {0, 1, 0}, // Y axis
        {0, 0, 1}  // Z axis
    };

    std::vector<glm::vec3> worldEgdes;
    worldEgdes.reserve(cubeLocalEdges.size());

    for (const auto& edge : cubeLocalEdges) {
        worldEgdes.push_back(rb.trans.rotation * edge);
    }

    return worldEgdes;
}

bool areOverlapping(const RigidBody& a, const RigidBody& b) {

    return true;
}

} // namespace phe::physics::collision

