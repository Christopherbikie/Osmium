cmake_minimum_required(VERSION 3.6)
project(osmium)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ../deps/glad/include
        ../deps/glfw/include
        ../deps/glm
        ../deps/imgui
        imgui
)

file(GLOB DEPS_SOURCES
        ../deps/glad/src/glad.c
        ../deps/imgui/*.h
        ../deps/imgui/*.cpp
)

set(SOURCE_FILES
        imgui/imgui_impl_glfw_gl3.cpp
        app/AppManager.cpp
        app/App.cpp
        app/Settings.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${DEPS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
