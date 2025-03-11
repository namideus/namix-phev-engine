#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

namespace phe::graphics {
    struct Window {
        GLFWwindow* nativeWindow;
        int width, height;
        std::string title;
    };

    /**
     * Allocates memory for a new window and sets its width, height and title.
     *
     * @return A pointer to the newly created window or nullptr if an error occurs.
     */
    Window* createWindow(int width, int height, const std::string& title);

    /**
     * Destroys the window and frees the memory allocated for it.
     */
    void destroyWindow(Window* window);

    /**
     * Initializes the window and sets up the OpenGL context.
     *
     * @return 0 if the window was successfully initialized, negative number
     * otherwise.
     */
    int initWindow(Window* window);

    /**
     * Calls for glfwPollEvents.
     */
    void pollEvents();

    /**
     * Calls for glfwSwapBuffers in the specified window.
     */
    void swapBuffers(Window* window);

    /**
     * This function calls for glfwWindowShouldClose in the specified window.
     *
     * @return true if the window should close, false otherwise.
     */
    bool shouldClose(Window* window);
}

#endif

