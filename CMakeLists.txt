cmake_minimum_required(VERSION 3.16)
project(pheV3 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically find all .cpp and .hpp files in src and include directories
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

# Add source files explicitly if needed
list(APPEND SRC_FILES src/graphics/window.cpp)

# Check if we found source files
if(NOT SRC_FILES)
  message(FATAL_ERROR "No source files found in the 'src' directory.")
endif()

# Create the physics engine as a static library
add_library(pheV3 STATIC ${SRC_FILES} ${HEADER_FILES})

# Include directories globally for all targets that link to pheV3
target_include_directories(pheV3 PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Find required packages
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

# Manually add GLEW and GLFW using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)

# Link libraries for pheV3
target_link_libraries(pheV3 PUBLIC OpenGL::GL ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})

# Include the GLEW and GLFW include directories
target_include_directories(pheV3 PUBLIC ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Add a demo executable (for testing and rendering)
add_executable(pheV3_demo tests/demo.cpp)
target_link_libraries(pheV3_demo PRIVATE pheV3)

