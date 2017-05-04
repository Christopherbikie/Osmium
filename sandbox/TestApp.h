#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>
#include <render/entity/components/Transform.h>
#include <render/entity/components/CameraPerspective.h>
#include <render/entity/Entity.h>
#include <render/scene/SceneManager.h>
#include <render/entity/components/CameraOrthographic.h>

class GLFWwindow;

class TestApp : public os::App
{
public:
	void run() override;

	void windowResizeCallback(glm::vec2 dimensions) override;

private:
	os::Shader *shader;
	os::VAO *vao;
	os::Texture *texture;
	os::Scene world;
	std::shared_ptr<os::Entity> mainCamera;
//	os::CameraOrthographic* camera; // Orthographic camera
};
