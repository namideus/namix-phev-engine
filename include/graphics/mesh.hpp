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

    Mesh createCubeMesh(float r, float g, float b);

    void destroyMesh(Mesh& mesh);

    /**
     * Draws the mesh in local space ( x: 0, y: 0, z: 0)
     */
    void drawMesh(Mesh &m);
}

#endif

