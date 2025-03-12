#include <GL/glew.h>

#include "graphics/mesh.hpp"

namespace phe::graphics {

Mesh createMesh(std::vector<float> vertices, std::vector<unsigned int> indices) {
    Mesh m;
    m.vertices = vertices;
    m.indices = indices;

    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);

    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);

    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(float),
                m.vertices.data(), GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.indices.size() * 
                sizeof(unsigned int), m.indices.data(), GL_STATIC_DRAW);

    // Position in local space
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
            (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return m;
}

void destroyMesh(Mesh &m) {
    glDeleteVertexArrays(1, &m.vao);
    glDeleteBuffers(1, &m.vbo);
    glDeleteBuffers(1, &m.vbo);

    m.vertices.clear();
    m.indices.clear();
}

void drawMesh(Mesh &m) {
    glBindVertexArray(m.vao);
    glDrawElements(GL_TRIANGLES, m.indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh createCubeMesh(float r, float g, float b) {
    std::vector<float> cubeVertices = {
        // Positions          // Colors
        -0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b 
    };

    std::vector<unsigned int> cubeIndices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 4, 7, 7, 3, 0,
        1, 5, 6, 6, 2, 1,
        3, 2, 6, 6, 7, 3,
        0, 1, 5, 5, 4, 0 
    };

    return createMesh(cubeVertices, cubeIndices);
}

} // namespace phe::graphics


