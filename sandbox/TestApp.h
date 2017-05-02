#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>
#include <render/entity/components/Transform.h>

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
	os::Transform<3, double_t> *transform;
	os::Transform<3, float_t> *cameraTransform;
	glm::mat4 projectionMat;
};
