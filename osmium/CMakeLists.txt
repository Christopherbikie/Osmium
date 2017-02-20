cmake_minimum_required(VERSION 3.6)
project(osmium)

set(CMAKE_CXX_STANDARD 14)

include_directories(
    ../deps/glad/include
    ../deps/glfw/include
)

file(GLOB DEPS_SOURCES ../deps/glad/src/glad.c)

set(SOURCE_FILES
    osmium.cpp
    osmium.h
)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${DEPS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
