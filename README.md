# Physics Engine V3 (pheV3)

## Overview

phe3V is a 3D Physics Engine library written in C++ made to showcase my abilities
in creating complex systems. It provides a robust framework to experiment with 
linear and angular motion of Rigid Bodies.

## Features

- Linear and angular motion integration.
- OpenGL wrappers (for things like windows, rendering, shaders).
- Easy implementation for real-time demos.

### Technologies
- C++
- CMake
- OpenGL
- GLFW
- glew
- glm (for math)

## Why this project?
I have built this project to push my limits as a software developer. With this
project I aim to:

- Demonstrate technical knowledge: Create high quality and polished engine
that will stand out in my portfolio, proving my capability of designing and 
building complex systems.

## What I have learned from this project:

- The laws of linear and angular motion, and how forces, torques and damping work together.
- C++ best practices, like memory management, clean code architecture and debugging.
- Practical experience integrating and using libraries like GLM, GLEW and GLFW.
- The importance of separation of concerns.
- How to design a reusable physics engine library that serves as a portfolio project.
- Problem solving and optimizations.
- The importance of clear documentation.

> **Note:** If you have ANY questions, feel free to contact me via the email listed on my profile
> I'm open to feedback, contributions and discussions!

# Code Example

How to create and utilize a window:

```cpp
int main() {
    phe::graphics::Window* window = phe::graphics::createWindow(800, 600, "Example pheV3");
    if (!window) {
        return 1;
    }

    if (phe::graphics::initWindow(window) < 0) {
        phe::graphics::destroyWindow(window);
        return 1;
    }

    while (!phe::graphics::shouldClose(window)) {
        phe::graphics::pollEvents();
        phe::graphics::swapBuffers(window);
    }

    phe::graphics::destroyWindow(window);
}
```

How to initialize the renderer and clear the window:

```cpp
// After initializing the window and before the loop
phe::graphics::Renderer renderer = phe::graphics::renderInit(window->width, window->height);

while (!phe::graphics::shouldCLose(window)) {
    // You must call this before rendering anything.
    graphics::renderClear(0.2f, 0.3f, 0.3f, 1.0f) // RGBA values you want, respectively.

    // rest of the code ...
}
```

I'M WORKING ON THE README. It's not done yet. I'll put more code examples soon.

