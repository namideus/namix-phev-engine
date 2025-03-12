#include "graphics/renderer.hpp"
#include "graphics/window.hpp"
#include "physics/rigidbody.hpp"

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

    graphics::Renderer renderer = graphics::renderInit(WIDTH, HEIGHT);

    physics::RigidBody b(0.5f, 0.2f, 0.2f);

    while (!graphics::shouldClose(window)) {
        graphics::renderClear(0.2f, 0.3f, 0.3f, 1.0f);

        graphics::drawRigidBody(b, renderer);
        physics::setPosition(b, 0.0f, 1.0f, b.trans.translation.z-0.01);

        graphics::swapBuffers(window);
        graphics::pollEvents();
    }

    graphics::destroyWindow(window);
    return 0;
}

