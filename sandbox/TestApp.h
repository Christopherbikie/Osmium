#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>
#include <render/entity/Entity.h>
#include <render/scene/SceneManager.h>
#include <input/Keyboard.h>

class GLFWwindow;

class TestApp : public os::App, public os::keyboard::KeyEventHandler
{
public:
	void run() override;

	void windowResizeCallback(glm::vec2 dimensions) override;

	void pressKey(uint32_t key) override;

private:
	std::shared_ptr<os::Shader> shader;
	os::Scene world;
	std::shared_ptr<os::LogicalEntity> mainCamera;
};

static float quadVertices[] = {
	-1.0f, 1.0f,
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,
};

static float quadTexCoords[] = {
	 0.0f, 1.0f,
	 0.0f, 0.0f,
	 1.0f, 0.0f,
	 0.0f, 1.0f,
	 1.0f, 0.0f,
	 1.0f, 1.0f,
};
