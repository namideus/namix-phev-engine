#include <glm/glm.hpp>
#include <vector>
#include <cstdlib>

#include "graphics/renderer.hpp"
#include "graphics/window.hpp"
#include "physics/rigidbody.hpp"

using namespace phe::graphics;
using namespace phe::physics;

#define WIDTH 1000
#define HEIGHT 800
#define MAX_BODIES 3

std::vector<RigidBody> bodies;

constexpr glm::vec3 GRAVITY(0.0f, -9.80665f, 0.0f);

glm::vec3 randomForce() {
    float theta = ((float)rand() / RAND_MAX) * 2.0f * M_PI; // Random azimuthal angle
    float phi = ((float)rand() / RAND_MAX) * M_PI; // Random elevation angle
    float magnitude = 10.0f + ((float)rand() / RAND_MAX) * 50.0f; // Between 10 and 60

    float x = sin(phi) * cos(theta);
    float z = cos(phi);

    return glm::vec3(x, 0.0f, z) * magnitude;
}

void spawnRigidBody() {
    float randX = ((float)rand() / RAND_MAX) * WIDTH - WIDTH / 2.0f;
    glm::vec3 pos(randX, HEIGHT + 5.0f, -3.0f);
    RigidBody newBody = RigidBody(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 116.0f, 217.0f), 1.0f);
    setPosition(newBody, pos);
    applyForce(newBody, randomForce(), glm::vec3(0.050f, 0.1f, 0.0f));
    bodies.push_back(newBody);
}

int main() {
    Window* window = createWindow(WIDTH, HEIGHT, "Raining Rigid Bodies Demo");
    if (!window) {
        return 1;
    }

    if (initWindow(window) < 0) {
        return 1;
    }

    Renderer renderer = renderInit(window->width, window->height);
    float lastTime = 0.0f;

    while (!shouldClose(window)) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;
        renderClear(30.0f, 30.0f, 40.0f, 1.0f);

        for (auto it = bodies.begin(); it != bodies.end(); ) {
            applyForce(*it, GRAVITY, glm::vec3(0.0f, 0.0f, 0.0f));
            integrateForces(*it, dt);
            integrateVelocity(*it, dt);

            if (it->trans.translation.y < -5.0f) {
                it = bodies.erase(it);
            } else {
                it++;
            }
        }

        if (bodies.size() < MAX_BODIES) {
            spawnRigidBody();
        }

        for (auto& body : bodies) {
            drawRigidBody(body, renderer);
        }

        swapBuffers(window);
        pollEvents();
    }

    destroyWindow(window);
}
