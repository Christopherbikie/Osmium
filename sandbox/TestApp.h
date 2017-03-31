#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>

class GLFWwindow;

class TestApp : public os::App
{
public:
	void run() override;

	void windowResizeCallback(glm::vec2 dimensions) override;

private:
	os::Shader *shader;
	os::VAO *vao;
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
};
