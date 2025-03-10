cmake_minimum_required(VERSION 3.16)
project(pheV3 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

# Check if we found source files
if(NOT SRC_FILES)
  message(FATAL_ERROR "No source files found in the 'src' directory.")
endif()

# Create the physics engine as a static library
add_library(pheV3 STATIC ${SRC_FILES} ${HEADER_FILES})

# Include directories globally
target_include_directories(pheV3 PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Find required libraries
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

# Manually add GLEW and GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)

# Link libraries
target_link_libraries(pheV3 PUBLIC glm OpenGL::GL ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
target_include_directories(pheV3 PUBLIC ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Add a test executable (for rendering & physics demos)
add_executable(pheV3_demo tests/demo.cpp)
target_link_libraries(pheV3_demo PRIVATE pheV3)

