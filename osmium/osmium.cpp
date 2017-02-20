#include "osmium.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace os
{
	GLFWwindow *window;

	bool init()
	{
		std::cout << "Hello, World!" << std::endl;

		if (!glfwInit())
		{
			std::cerr << "ERROR: GLFW failed to initialize.\n";
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		int width = 800, height = 600;
		window = glfwCreateWindow(width, height, "Osmium", nullptr, nullptr);

		glfwMakeContextCurrent(window);

		if (!window)
		{
			std::cerr << "ERROR: Window context failed to initialize.\n";
			glfwTerminate();
			return false;
		}

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			std::cout << "ERROR: Failed to initialize OpenGL context.\n";
			glfwTerminate();
			return false;
		}

		return true;
	}

	void run()
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.3f, 0.1f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwPollEvents();

			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}