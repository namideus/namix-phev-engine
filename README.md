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

# Demos

###### First Demo of pheV3

A really simple demonstration showcasing the first features of the Physics Engine.

[pheV3 demo1](https://youtu.be/5l4_gwmBWSU)

> **Note:** I'll add new demos for every feature added, so more demos soon :D

# How to build

## First-time setup
When building for the first time, you need to generate `compile_commands.json`
using Bear and then move it down a folder.

First, install Bear.

Ubuntu/Debian:
```bash
sudo apt update
sudo apt install bear
```

Arch Linux:
```bash
sudo pacman -S bear
```

macOS (Homebrew):
```bash
brew install bear
```

Windows (MSYS2 - Pacman)
```bash
pacman -S mingw-w64-x86_64-bear
```

Then create the build directory and build with CMake and bear:
```bash
mkdir build
cd build
cmake ..
bear -- cmake --build .
mv compile_commands.json ..
```

## Building the project
After that, you can always build and compile with these commands inside the pheV3 folder:

```bash
cd ..
cmake -S . -B build
cmake --build build
```

Everything should work. If not, contact me for help :D.

# Code Example

How to create and utilize a window:

```cpp
int main() {
    // create a window with specified width, height and title
    phe::graphics::Window* window = phe::graphics::createWindow(800, 600, "Example pheV3");
    if (!window) {
        return 1;
    }

    // initialize the window
    if (phe::graphics::initWindow(window) < 0) {
        phe::graphics::destroyWindow(window);
        return 1;
    }

    // main loop
    while (!phe::graphics::shouldClose(window)) {
        phe::graphics::pollEvents();
        phe::graphics::swapBuffers(window);
    }

    phe::graphics::destroyWindow(window); // Clean up and free window
}
```

How to initialize the renderer and clear the window:

```cpp
// After initializing the window and before the loop
phe::graphics::Renderer renderer = phe::graphics::renderInit(window->width, window->height);

while (!phe::graphics::shouldClose(window)) {
    // clear the window with specified RGBA respectively
    graphics::renderClear(0.2f, 0.3f, 0.3f, 1.0f);

    // Render other stuff here...
}
```

How to draw a static Rigid Body:

```cpp
#include <glm/glm.hpp>

/* ... */

// Inside main
phe::physics::RigidBody rigidBody(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.8f, 0.2f, 0.3f), 1.0f) // Size vector, RGB vector, mass


// Inside the render loop 
phe::graphics::drawRigidBody(rigidBody, renderer); // draw the body using the renderer
```

I'M WORKING ON THE README. It's not done yet. I'll put more code examples soon.

