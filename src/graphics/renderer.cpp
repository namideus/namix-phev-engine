#include <GL/glew.h>

#include "graphics/renderer.hpp"

namespace phe::graphics {

void renderClear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer renderInit() {
    Renderer r;
    r.shader = new Shader("./src/graphics/shaders/vert.glsl", "./src/graphics/shaders/frag.glsl");

    r.shader->use();

    return r;
}

Renderer::Renderer() : shader(nullptr){ }
Renderer::~Renderer() { delete shader; }
    
} // namespace phe::graphics

