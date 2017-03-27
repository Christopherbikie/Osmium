#include "TestApp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

void TestApp::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.3f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::ShowTestWindow();

		ImGui::Render();

		glfwSwapBuffers(mWindow);
	}
}
