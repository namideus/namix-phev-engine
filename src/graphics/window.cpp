#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/window.hpp"

using namespace phe;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

graphics::Window* graphics::createWindow(int width, int height, const std::string &title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window* window = new Window;
    if (!window) {
        std::cerr << "Failed to allocate memory for window\n";
        return nullptr;
    }

    window->width = width;
    window->height = height;
    window->title = title;

    window->nativeWindow = glfwCreateWindow(width, height, title.c_str(),
            nullptr, nullptr);

    return window;
}

void graphics::destroyWindow(phe::graphics::Window *window) {
    glfwDestroyWindow(window->nativeWindow);
    delete window;
    glfwTerminate();
}

int graphics::initWindow(phe::graphics::Window* window) {
    if (!window) {
        std::cerr << "Couldn't initialize, window is nullptr\n";
        return -1;
    }
    glfwMakeContextCurrent(window->nativeWindow);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -2;
    }

    glfwSetFramebufferSizeCallback(window->nativeWindow, framebuffer_size_callback);

    return 0;
}

void graphics::pollEvents() {
    glfwPollEvents();
}

void graphics::swapBuffers(phe::graphics::Window* window) {
    glfwSwapBuffers(window->nativeWindow);
}

bool graphics::shouldClose(phe::graphics::Window* window) {
    return glfwWindowShouldClose(window->nativeWindow);
}

