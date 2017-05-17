cmake_minimum_required(VERSION 3.6)
project(osmium)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ../deps/glad/include
        ../deps/glfw/include
        ../deps/glm
        ../deps/imgui
        ../deps/Simple-OpenGL-Image-Library/src
		../deps/tinyobjloader
)

file(GLOB DEPS_SOURCES
        ../deps/glad/src/glad.c
        ../deps/imgui/*.h
        ../deps/imgui/*.cpp
		../deps/tinyobjloader/tiny_obj_loader.cc
)

set(SOURCE_FILES
        imgui/imgui_impl_glfw_gl3.cpp
        app/AppManager.cpp
        app/App.cpp
        app/Settings.cpp
		input/Keyboard.cpp
		input/Mouse.cpp
        render/entity/Entity.cpp
		render/entity/components/BaseComponent.cpp
		render/entity/components/Camera.cpp
		render/entity/components/CameraOrthographic.cpp
		render/entity/components/CameraPerspective.cpp
		render/entity/components/MeshComponent.cpp
		render/entity/components/PlayerControlFPV.cpp
		render/entity/LogicalEntity.cpp
		render/scene/SceneManager.cpp
		render/mesh/Mesh.cpp
		render/mesh/Material.cpp
		render/graphics/Shader.cpp
        render/graphics/Texture.cpp
        render/graphics/VAO.cpp
		render/graphics/Light.cpp
		render/graphics/PointLight.cpp
        util/Loader.cpp
		render/entity/components/PointLight.cpp render/entity/components/PointLight.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${DEPS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} SOIL ${SOIL_LIBRARIES})
