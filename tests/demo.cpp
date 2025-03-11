#include "graphics/window.hpp"
#include "graphics/mesh.hpp"
#include "graphics/renderer.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace phe;

int main() {
    auto window = graphics::createWindow(WIDTH, HEIGHT, "pheV3");
    if (!window) {
        return 1;
    }

    if (graphics::initWindow(window) < 0) {
        graphics::destroyWindow(window);
        return 1;
    }

    // Test mesh rendering
    graphics::Mesh mesh = graphics::createCubeMesh();

    while (!graphics::shouldClose(window)) {
        graphics::renderClear(0.2f, 0.3f, 0.3f, 1.0f);

        graphics::drawMesh(mesh);

        graphics::swapBuffers(window);
        graphics::pollEvents();
    }

    graphics::destroyWindow(window);
    return 0;
}

