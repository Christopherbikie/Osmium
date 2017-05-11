#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>
#include <input/Keyboard.h>
#include <render/scene/SceneManager.h>

class GLFWwindow;

class TestApp : public os::App, public os::keyboard::KeyEventHandler
{
public:
	void run() override;

	void windowResizeCallback(glm::vec2 dimensions) override;

	void pressKey(uint32_t key) override;

private:
	std::shared_ptr<os::Scene> scene;
	std::shared_ptr<os::LogicalEntity> cameraEntity;
};
