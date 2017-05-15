#pragma once

#include <glm/vec2.hpp>

class GLFWwindow;

namespace os
{
	namespace mouse
	{
		class ScrollEventHandler
		{
		public:
			virtual ~ScrollEventHandler()
			{}
			virtual void scroll(glm::ivec2 offset) = 0;
		};

		void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition);
		void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void addScrollHandler(ScrollEventHandler *handler);

		glm::ivec2& getPosition();
		glm::ivec2& getMovement();
		
		void setCaptured(bool value);
		void toggleCaptured();
		bool isCaptured();

		void update();
	};
}
