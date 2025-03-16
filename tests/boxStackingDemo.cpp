#include <glm/glm.hpp>

#include "graphics/renderer.hpp"
#include "graphics/window.hpp"
#include "physics/physicsWorld.hpp"
#include "physics/rigidbody.hpp"

using namespace phe;

float lastTime = 0.0f;

int main() {
    auto window = graphics::createWindow(800, 600, "Collision Detection Test");
    if (!window) {
        return 1;
    }

    if (graphics::initWindow(window) < 0) {
        return 1;
    }

    auto renderer = graphics::renderInit(window->width, window->height);

    physics::RigidBody rb1(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, true);
    physics::RigidBody rb2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, true);

    physics::setPosition(rb1 ,glm::vec3(-4.0f, -3.0f, 0.0f));
    physics::setPosition(rb2, glm::vec3(4.0f, -3.0f, 0.0f));

    physics::PhysicsWorld world;

    world.addRigidBody(&rb2);
    world.addRigidBody(&rb1);

    physics::applyForce(rb1, glm::vec3(40.0f, 90.0f, -50.0f), glm::vec3(0.1f, 0.0f, 0.1f));
    physics::applyForce(rb2, glm::vec3(-40.0f, 90.0f, -50.0f), glm::vec3(0.1f, 0.0f, 0.2f));

    while (!graphics::shouldClose(window)) {
        graphics::renderClear(0.2f, 0.3f, 0.3f, 1.0f);

        float currentTime = static_cast<float>(glfwGetTime());
        float dt = currentTime - lastTime;
        world.update(dt, renderer);

        lastTime = currentTime;

        graphics::pollEvents();
        graphics::swapBuffers(window);
    }

    graphics::destroyWindow(window);
}


