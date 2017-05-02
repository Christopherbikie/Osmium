#pragma once

#include <app/App.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <render/graphics/Texture.h>

class GLFWwindow;

class TestApp : public os::App
{
public:
	void run() override;
};
