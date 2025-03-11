cmake_minimum_required(VERSION 3.10)
project(pheV3)

# Set policy CMP0072 to prefer GLVND if available
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the main include directory for all targets
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find packages and external libraries
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)
find_package(GTest REQUIRED)

# (Optional) Print the found libraries for debugging
message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")

# Collect source files for the main library
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create the main library target
add_library(pheV3 STATIC ${SRC_FILES})

# Link external libraries to the main library target
target_link_libraries(pheV3 PUBLIC OpenGL::GL ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})

# Collect test source files
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# Create the test executable target
add_executable(pheV3_tests ${TEST_FILES})

# Link the test executable with the main library and Google Test libraries
target_link_libraries(pheV3_tests PRIVATE pheV3 GTest::GTest GTest::Main)

# Ensure tests can find headers in the include directory
target_include_directories(pheV3_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Enable CTest and add the test
enable_testing()
add_test(NAME pheV3_tests COMMAND pheV3_tests)

# Optionally, create a demo executable
add_executable(pheV3_demo tests/demo.cpp)
target_link_libraries(pheV3_demo PRIVATE pheV3)

