#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class GLFWwindow;

namespace os
{
	class App
	{
	public:
		App();
		~App();

		bool initGL();
		virtual void run() = 0;

		GLFWwindow* getWindow();

		void setWindowSize(glm::vec2 dimensions);
		virtual void windowResizeCallback(glm::vec2 dimensions);

	protected:
		GLFWwindow *mWindow;

		void newFrame();

	private:
		bool mInitialised;
	};
}
