cmake_minimum_required(VERSION 3.6)
project(Osmium)

set(CMAKE_CXX_STANDARD 14)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(deps/glfw)

add_subdirectory(deps/Simple-OpenGL-Image-Library)

add_subdirectory(osmium)
add_subdirectory(sandbox)
add_subdirectory(nbody)
