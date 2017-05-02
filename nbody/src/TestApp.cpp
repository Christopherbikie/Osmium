#include "TestApp.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/Transform.h>
#include "app/Settings.h"

using namespace os;

void TestApp::run()
{
	settings::setWindowTitle("n-body simulation by Chris and Matt");

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		float_t delta = 1000.0f / ImGui::GetIO().Framerate;

		// GUI

		ImGui::Text("Hello, world!");
		glm::vec2 viewport = settings::getViewport();
		ImGui::Text("Viewport: x: %.0f y: %.0f", viewport.x, viewport.y);

		static GLchar buf[64] = "";
		ImGui::InputText("Window Title", buf, 64);
		if (ImGui::Button("Set"))
			settings::setWindowTitle(buf);

		glm::vec3 clearColor = settings::getClearColour();
		ImGui::ColorEdit3("Clear color", (GLfloat *) &clearColor);
		settings::setClearColour(clearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", delta, ImGui::GetIO().Framerate);

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);
	}
}
