#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>

namespace phe::graphics {
    struct Mesh {
        unsigned int vao, vbo, ebo;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    Mesh createMesh(std::vector<float> vertices, 
                    std::vector<unsigned int> indices);

    Mesh createCubeMesh(glm::vec3 size, glm::vec3 rgb);

    void destroyMesh(Mesh& mesh);

    /**
     * Draws the mesh in local space ( x: 0, y: 0, z: 0)
     */
    void drawMesh(Mesh &m);
}

#endif

