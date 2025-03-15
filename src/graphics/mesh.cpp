#include <GL/glew.h>
#include <stdexcept>
#include <glm/gtc/quaternion.hpp>

#include "graphics/mesh.hpp"
#include "math_utils/transform.hpp"

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

/**
 * @param size The size of the cube.
 *
 * @param r Red value of the cube.
 * @param g Green value of the cube.
 * @param b Blue value of the cube.
 */
Mesh createCubeMesh(glm::vec3 size, glm::vec3 rgb) {
    float hx = size.x * 0.5;
    float hy = size.y * 0.5;
    float hz = size.z * 0.5;

    float r = rgb.x;
    float g = rgb.y;
    float b = rgb.b;

    std::vector<float> cubeVertices = {
        -hx, -hy,  hz,  r, g, b,
         hx, -hy,  hz,  r, g, b,
         hx,  hy,  hz,  r, g, b,
        -hx,  hy,  hz,  r, g, b,

        -hx, -hy, -hz,  r, g, b,
        -hx,  hy, -hz,  r, g, b,
         hx,  hy, -hz,  r, g, b,
         hx, -hy, -hz,  r, g, b,

        -hx, -hy, -hz,  r, g, b,
        -hx, -hy,  hz,  r, g, b,
        -hx,  hy,  hz,  r, g, b,
        -hx,  hy, -hz,  r, g, b,

         hx, -hy, -hz,  r, g, b,
         hx,  hy, -hz,  r, g, b,
         hx,  hy,  hz,  r, g, b,
         hx, -hy,  hz,  r, g, b,

        -hx,  hy, -hz,  r, g, b,
        -hx,  hy,  hz,  r, g, b,
         hx,  hy,  hz,  r, g, b,
         hx,  hy, -hz,  r, g, b,

         hx, -hy, -hz,  r, g, b,
         hx, -hy,  hz,  r, g, b,
        -hx, -hy,  hz,  r, g, b,
        -hx, -hy, -hz,  r, g, b,
    };


    std::vector<unsigned int> cubeIndices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    return createMesh(cubeVertices, cubeIndices);
}

int getNumVerts(Mesh& m) {
    return m.vertices.size() / 6;
}

glm::vec3 getVertex(Mesh& m, math::Transform trans, int i) {
    if (i > m.vertices.size() || i < 0) {
        throw std::out_of_range("Vertex index is out of range");
    }

    int vertexStart = i * 6;

    glm::vec3 localVertex(
        m.vertices[vertexStart],
        m.vertices[vertexStart + 1],
        m.vertices[vertexStart + 2]
    );

    return glm::vec3(trans.rotation * glm::vec4(localVertex, 1.0f)) + trans.translation;
}

} // namespace phe::graphics

