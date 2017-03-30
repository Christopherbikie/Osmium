cmake_minimum_required(VERSION 3.6)
project(sandbox)

set(CMAKE_CXX_STANDARD 14)

include_directories(GLOB
        ../osmium
        ../osmium/*
        ../deps/imgui
        ../deps/glad/include
        ../deps/glm)

set(SOURCE_FILES
        main.cpp
        TestApp.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} osmium)