#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>
#include <input/Keyboard.h>
#include <render/scene/SceneManager.h>
#include <input/Mouse.h>

class GLFWwindow;

class NBodyApp :
		public os::App,
		private os::keyboard::KeyEventHandler,
		private os::mouse::ScrollEventHandler
{
public:
	void run() override;

	void windowResizeCallback(glm::vec2 dimensions) override;

	void pressKey(uint32_t key) override;
	void scroll(glm::ivec2 offset) override;

private:
	std::shared_ptr<os::Scene> scene;
	std::shared_ptr<os::LogicalEntity> cameraEntity;
};
