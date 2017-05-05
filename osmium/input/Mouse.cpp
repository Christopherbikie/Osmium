#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "../app/AppManager.h"

namespace os
{
	namespace mouse
	{
		glm::ivec2 position;
		glm::ivec2 difference;
		bool captured = false;

		void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition)
		{
			glm::ivec2 newPosition = glm::ivec2(xPosition, yPosition);
			if (position.x != -1)
				difference = newPosition - position;
			position = newPosition;
		}

		glm::ivec2& getPosition()
		{
			return position;
		}

		glm::ivec2& getMovement()
		{
			return difference;
		}

		void setCaptured(bool value)
		{
			GLFWwindow *window = AppManager::instance()->getWindow();
			if (value)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				position = glm::ivec2(-1, -1);
			}
			else
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			captured = value;
		}

		void toggleCaptured()
		{
			setCaptured(!captured);
		}

		bool isCaptured()
		{
			return captured;
		}

		void update()
		{
			difference = glm::ivec2(0);
		}
	}
}
