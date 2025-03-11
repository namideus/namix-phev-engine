#include "graphics/window.hpp"

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

    while (!graphics::shouldClose(window)) {
        graphics::swapBuffers(window);
        graphics::pollEvents();
    }

    graphics::destroyWindow(window);
    return 0;
}

