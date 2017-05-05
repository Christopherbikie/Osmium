#include "Settings.h"
#include <glad/glad.h>

namespace os
{
	namespace settings
	{
		glm::vec2 viewportSize = glm::vec2(800, 600);
		glm::vec3 clearColour = glm::vec3(0.3f, 0.1f, 0.5f);

		GLbitfield clearBits = (GLbitfield) (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::string windowTitle = "Osmium Engine";

		const glm::vec2 &getViewport()
		{
			return viewportSize;
		}

		void setViewport(const glm::vec2 &newViewportSize)
		{
			viewportSize = newViewportSize;
		}

		const float_t getAspectRatio()
		{
			return viewportSize.x / viewportSize.y;
		}

		const glm::vec3 &getClearColour()
		{
			return clearColour;
		}

		void setClearColour(const glm::vec3 &newClearColour)
		{
			clearColour = newClearColour;
		}

		GLbitfield getClearBits()
		{
			return clearBits;
		}

		void setClearBits(GLbitfield newClearBits)
		{
			clearBits = newClearBits;
		}

		void setClearBits(unsigned int bits, bool value)
		{
			if (value)
				clearBits |= bits;
			else
				clearBits &= ~bits;
		}

		const std::string &getWindowTitle()
		{
			return windowTitle;
		}

		void setWindowTitle(const std::string &newWindowTitle)
		{
			windowTitle = newWindowTitle;
		}
	}
}
