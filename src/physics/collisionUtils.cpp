#include "physics/collisionUtils.hpp"
#include "graphics/mesh.hpp"
#include "physics/rigidbody.hpp"
#include <glm/geometric.hpp>

namespace phe::physics::collision {

float projectOntoAxis(const glm::vec3& vertex, const glm::vec3& axis) {
    return glm::dot(vertex, axis);
}

bool projectionsOverlap(float minA, float maxA, float minB, float maxB) {
    return !(maxA < minB || maxB < minA);
}
    
std::vector<glm::vec3> computeCubeNormals(const RigidBody &rb) {
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
        // Get world normals by transforming local normals with the rigid body's rotation
        worldNormals.push_back(rb.trans.rotation * normal);
    }

    return worldNormals;
}

std::vector<glm::vec3> computeCubeEdges(const RigidBody& rb) {
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

bool areColliding(RigidBody& a, RigidBody& b) {
    std::vector<glm::vec3> axes;    

    auto normalsA = computeCubeNormals(a);
    auto normalsB = computeCubeNormals(b);

    axes.insert(axes.begin(), normalsA.begin(), normalsA.end());
    axes.insert(axes.begin(), normalsB.begin(), normalsB.end());

    auto edgesA = computeCubeEdges(a);
    auto edgesB = computeCubeEdges(b);

    // Calculate axis from cross product between every edge from body A and every edge from body B
    for (auto& a : edgesA) {
        for (auto& b : edgesB) {
            glm::vec3 res = glm::normalize(glm::cross(a, b));
            // ignore 0 length cross
            if (glm::length(res) > 0.0f) 
                axes.push_back(res);
        }
    }

    for (auto& axis : axes) {
        // Find minA, maxA, minB and maxB to check if projection ovelaps
        float minA = FLT_MAX, maxA = -FLT_MAX;
        for (int i = 0; i < graphics::getNumVerts(a.mesh); ++i) {
            glm::vec3 vA = graphics::getVertex(a.mesh, a.trans, i);
            float projectionA = projectOntoAxis(vA, axis);
            minA = std::min(minA, projectionA);
            maxA = std::max(maxA, projectionA);
        }

        float minB = FLT_MAX, maxB = -FLT_MAX;
        for (int i = 0; i < graphics::getNumVerts(b.mesh); ++i) {
            glm::vec3 vA = graphics::getVertex(b.mesh, b.trans, i);
            float projectionB = projectOntoAxis(vA, axis);
            minB = std::min(minB, projectionB);
            maxB = std::max(maxB, projectionB);
        }

        if (!projectionsOverlap(minA, maxA, minB, maxB)) {
            return false;
        }
    }

    return true;
}

} // namespace phe::physics::collision

