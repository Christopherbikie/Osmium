#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include "App.h"
#include <iostream>
namespace os
{
	App::App() : mWindow(nullptr), mInitialised(false)
	{
	}
		
	App::~App()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		if (mWindow)
			glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	bool App::initGL()
	{
		if (mInitialised)
		{
			std::cerr << "Warning: delete App before running init() a second time\n";
			return true;
		}

		if (!glfwInit())
		{
			std::cerr << "ERROR: GLFW failed to initialize.\n";
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		int width = 800, height = 600;
		mWindow = glfwCreateWindow(width, height, "Osmium", nullptr, nullptr);
		if (!mWindow)
		{
			std::cerr << "ERROR: Window context failed to initialize.\n";
			return false;
		}
		glfwMakeContextCurrent(mWindow);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			std::cerr << "ERROR: Failed to initialize OpenGL context.\n";
			return false;
		}

		ImGui_ImplGlfwGL3_Init(mWindow, true);

		if (!init())
		{
			std::cerr << "ERROR: App::init() returned false\n";
			return false;
		}

		mInitialised = true;
		return true;
	}

	bool App::init()
	{
		return true;
	}

	GLFWwindow *App::getWindow()
	{
		return mWindow;
	}
}
