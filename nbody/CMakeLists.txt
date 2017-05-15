cmake_minimum_required(VERSION 3.6)
project(nbody)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/build)

include_directories(GLOB
        ../osmium
        ../osmium/*
        ../deps/imgui
        ../deps/glad/include
        ../deps/glm)

set(SOURCE_FILES
        src/components/PhysicsComponent.h
        src/components/PathComponent.h
		src/main.cpp
		src/NBodyApp.cpp
		src/UI.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} osmium)


# Physics test

include_directories(GLOB /deps/glm)

set(PT_SOURCE_FILES
        src/math/Physics.h
		src/math/PhysicsTest.cpp)

add_executable(${PROJECT_NAME}-physics-test ${PT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})
