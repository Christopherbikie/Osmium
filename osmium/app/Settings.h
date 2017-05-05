#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <cmath>

typedef unsigned int GLbitfield;

namespace os
{
	namespace settings
	{
		const glm::vec2 &getViewport();
		void setViewport(const glm::vec2 &newViewportSize);
		const float_t getAspectRatio();

		const std::string &getWindowTitle();
		void setWindowTitle(const std::string &newWindowTitle);

		GLbitfield getClearBits();
		void setClearBits(GLbitfield clearBits);
		void setClearBits(unsigned int bit, bool value);

		const glm::vec3 &getClearColour();
		void setClearColour(const glm::vec3 &newClearColour);


	};
}
