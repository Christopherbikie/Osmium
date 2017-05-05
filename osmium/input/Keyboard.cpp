#include "Keyboard.h"
#include <imgui.h>
#include "../imgui/imgui_impl_glfw_gl3.h"

namespace os
{
	namespace keyboard
	{
		bool keys[1024];
		std::map<GLuint, std::vector<KeyEventHandler *>> keyHandlers;

		void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
		{
			ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mode);

			ImGuiIO &io = ImGui::GetIO();
			if (io.WantCaptureKeyboard)
				return;

			if (key >= 0 && key < 1024)
			{
				if (action == GLFW_PRESS)
					keys[key] = true;
				else if (action == GLFW_RELEASE)
					keys[key] = false;
			}
			if (action == GLFW_PRESS)
				for (KeyEventHandler *handler : keyHandlers[key])
					handler->pressKey(key);
		}

		bool isKeyDown(int key)
		{
			return keys[key];
		}

		void addKeyHandler(GLuint key, KeyEventHandler *handler)
		{
			keyHandlers[key].push_back(handler);
		}

		void releaseAllKeys()
		{
			for (bool key : keys)
				key = false;
		}
	}
}
