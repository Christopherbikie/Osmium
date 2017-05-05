#pragma once

#include <glm/vec2.hpp>

class GLFWwindow;

namespace os
{
	namespace mouse
	{
		void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition);

		glm::ivec2& getPosition();
		glm::ivec2& getMovement();
		
		void setCaptured(bool value);
		void toggleCaptured();
		bool isCaptured();

		void update();
	};
}
