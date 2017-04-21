#include <imgui.h>

#include "AppManager.h"
#include "App.h"
#include "Settings.h"

#include "../imgui/imgui_impl_glfw_gl3.h"
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

		glEnable(GL_DEPTH_TEST);
		glfwSetFramebufferSizeCallback(mWindow, AppManager::framebufferSizeCallback);

		ImGui_ImplGlfwGL3_Init(mWindow, true);

		mInitialised = true;
		return true;
	}

	GLFWwindow *App::getWindow()
	{
		return mWindow;
	}

	void App::newFrame()
	{
		glfwSetWindowTitle(mWindow, settings::getWindowTitle().c_str());

		glm::vec3 clearColour = settings::getClearColour();
		glClearColor(clearColour.r, clearColour.g, clearColour.b, 1.0f);
		glClear(settings::getClearBits());

		glfwPollEvents();

		ImGui_ImplGlfwGL3_NewFrame();
	}

	void App::setWindowSize(glm::vec2 dimensions)
	{
		if (dimensions.x > 0 && dimensions.y > 0)
			glfwSetWindowSize(mWindow, (int) dimensions.x, (int) dimensions.y);
	}

	void App::windowResizeCallback(glm::vec2 dimensions)
	{
	}
}
