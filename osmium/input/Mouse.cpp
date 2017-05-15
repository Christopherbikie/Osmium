#include <GLFW/glfw3.h>
#include <vector>
#include "Mouse.h"
#include "../app/AppManager.h"
#include <imgui.h>
#include "../imgui/imgui_impl_glfw_gl3.h"

namespace os
{
	namespace mouse
	{
		glm::ivec2 cursorPosition;
		glm::ivec2 cursorDifference;
		glm::ivec2 scrollOffset;
		bool captured = false;

		std::vector<ScrollEventHandler *> scrollHandlers;

		void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition)
		{
			glm::ivec2 newPosition = glm::ivec2(xPosition, yPosition);
			if (cursorPosition.x != -1)
				cursorDifference = newPosition - cursorPosition;
			cursorPosition = newPosition;
		}

		void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
		{
			ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);

			ImGuiIO &io = ImGui::GetIO();
			if (io.WantCaptureMouse)
				return;

			scrollOffset = glm::ivec2((int) xoffset, (int) yoffset);

			for (ScrollEventHandler *handler : scrollHandlers)
				handler->scroll(scrollOffset);
		}

		void addScrollHandler(ScrollEventHandler *handler)
		{
			scrollHandlers.push_back(handler);
		}

		glm::ivec2& getPosition()
		{
			return cursorPosition;
		}

		glm::ivec2& getMovement()
		{
			return cursorDifference;
		}

		void setCaptured(bool value)
		{
			GLFWwindow *window = AppManager::instance()->getWindow();
			if (value)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				cursorPosition = glm::ivec2(-1, -1);
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
			cursorDifference = glm::ivec2(0);
			scrollOffset = glm::ivec2(0);
		}
	}
}
