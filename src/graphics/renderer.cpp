#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "graphics/renderer.hpp"

namespace phe::graphics {

void renderClear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer renderInit(const float windowWidth, const float windowHeight) {
    Renderer r;
    r.shader = new Shader("./src/graphics/shaders/vert.glsl", "./src/graphics/shaders/frag.glsl");
    r.shader->use();

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            (float)windowWidth/(float)windowHeight, 0.1f, 1000.0f);

    r.shader->setMat4("view", view);
    r.shader->setMat4("projection", projection);

    glEnable(GL_DEPTH_TEST);

    return r;
}

void drawRigidBody(physics::RigidBody& rb, Renderer& r) {
    auto model = math::toMatrix(rb.trans);
    r.shader->setMat4("model", model);
    drawMesh(rb.mesh);
}

Renderer::Renderer() : shader(nullptr){ }
Renderer::~Renderer() { delete shader; }
    
} // namespace phe::graphics

