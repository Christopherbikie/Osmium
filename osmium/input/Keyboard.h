#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

namespace os
{
	namespace keyboard
	{
		class KeyEventHandler
		{
		public:
			virtual ~KeyEventHandler()
			{}
			virtual void pressKey(uint32_t key) = 0;
		};

		void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
		bool isKeyDown(int key);
		void addKeyHandler(GLuint key, KeyEventHandler *handler);
		void releaseAllKeys();
	}
}
