# Physics Engine V3 (pheV3)

# pheV3 Physics Engine

## Overview

pheV3 is a custom physics engine project built to showcase advanced skills in
simulating realistic physics. The engine focuses on both linear and rotational 
motion, offering a robust framework for experimenting with and demonstrating 
physical behaviors in a virtual environment.

> **Note:** This project is in its very early stages, so most of the planned 
features aren't implemented yet. They will be added step by step as development 
progresses.

## Project Goals

- **Accurate Simulation:** Implement and simulate linear motion 
(position, velocity, acceleration) along with rotational dynamics 
(angular velocity, torque, and orientation using quaternions).
- **Modular & Maintainable Code:** Structure the engine into discrete, testable
modules so that each component (e.g., force integration, collision handling) 
can be developed and refined independently.
- **High-Quality Demos:** Create polished visual demos that clearly demonstrate
the engine's capabilities.
- **Automated Testing:** Establish a solid testing framework to ensure every 
part of the engine works as expected, helping to catch bugs early and 
streamline future improvements.

## What I Plan to Do

- **Core Engine Development:**  
  - Implement basic linear motion using Newtonian mechanics.  
  - Integrate rotational motion to simulate realistic object dynamics, 
  including angular acceleration and torque.
- **Integration of Essential Libraries:**  
  - Use **GLM** for all math operations (vectors, matrices, quaternions).  
  - Use **OpenGL** for rendering, with **GLEW** and **GLFW** to handle 
  windowing and OpenGL context management.
- **Robust Testing & Continuous Integration:**  
  - Develop comprehensive unit tests to verify each engine component.
  - Set up a CI system to automatically run tests on every commit.
- **Visual Demonstrations:**  
  - Build a demo application that uses the engine to display both linear and 
  rotational motion in real time.

## Technologies Used

- **C++17:** Primary language for system-level performance.
- **CMake:** For cross-platform build configuration.
- **GLM:** For mathematical computations (vectors, matrices, quaternions).
- **OpenGL, GLEW, GLFW:** For rendering and managing graphical output.
- **Unit Testing Framework:** (e.g., Google Test, Catch2, or Doctest) for 
automated testing.

## Why This Project?

This project is driven by a desire to push the boundaries of what I can achieve
as an engineer. By tackling the challenges of simulating both linear and 
rotational motion, I aim to:

- **Master Complex Concepts:** Deepen my understanding of physics simulations
and learn to optimize performance in a challenging, real-world scenario.
- **Demonstrate Technical Excellence:** Create a high-quality, well-tested
engine that stands out as a portfolio piece, proving my ability to handle 
complex systems with precision.
- **Embrace Best Practices:** Commit to disciplined, modular development and
rigorous testing—key practices that ensure both reliability and scalability in
professional software projects.

This project is a personal challenge to reach new heights in engineering and to 
build something that not only works well but also showcases a commitment to 
innovation and quality.

---

