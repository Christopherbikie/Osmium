#include "TestApp.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <glm/vec2.hpp>
#include "app/Settings.h"

using namespace os;

void TestApp::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();

		ImGui::Text("Hello, world!");
		glm::vec2 viewport = settings::getViewport();
		ImGui::Text(("Viewport: x: " + std::to_string(viewport.x) + " y: " + std::to_string(viewport.y)).c_str());

		static char buf[64] = "";
		ImGui::InputText("Window Title", buf, 64);
		if (ImGui::Button("Set"))
			settings::setWindowTitle(buf);

		glm::vec3 clearColor = settings::getClearColour();
		ImGui::ColorEdit3("Clear color", (float*)&clearColor);
		settings::setClearColour(clearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Render();

		glfwSwapBuffers(mWindow);
	}
}
