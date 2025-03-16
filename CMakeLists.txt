cmake_minimum_required(VERSION 3.10)
project(pheV3)

# Set policy CMP0072 to prefer GLVND if available
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -----------------------------------------------
# Critical Fix: Replace global include_directories with target-specific includes
# -----------------------------------------------

# Find packages and external libraries
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)
find_package(GTest REQUIRED)

# Create the main library target FIRST
add_library(pheV3 STATIC)

# Set PUBLIC include directory for the library
target_include_directories(pheV3
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include  # Allows anyone linking to pheV3 to find headers
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src      # Optional, if headers are shared between sources
)

# Add sources to the library (keep your GLOB if preferred, but be aware of caveats)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
target_sources(pheV3 PRIVATE ${SRC_FILES})

# Link dependencies
target_link_libraries(pheV3
  PUBLIC
    OpenGL::GL
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# Tests and executables
enable_testing()

# Tests executable (link to pheV3 to inherit includes)
# Demo executables
add_executable(singleBodyDemo tests/singleBodyDemo.cpp)
add_executable(collisionDetectionTest tests/collisionDetectionTest.cpp)
add_executable(boxStackingDemo tests/boxStackingDemo.cpp)
target_link_libraries(singleBodyDemo PRIVATE pheV3)
target_link_libraries(collisionDetectionTest PRIVATE pheV3)
target_link_libraries(boxStackingDemo PRIVATE pheV3)

