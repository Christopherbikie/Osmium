#include "TestApp.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <glm/vec2.hpp>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include "app/Settings.h"

using namespace os;

void TestApp::run()
{
	Shader *shader = new os::Shader;
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	float_t vertices[] = {
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
	};
	float_t colours[] = {
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.3f, 0.1f, 0.5f,
	};
	uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3,
	};

	VAO *vao = new VAO;
	vao->storeInBuffer(0, 3, 4, vertices);
	vao->storeInBuffer(1, 3, 4, colours);
	vao->storeInElementBuffer(6, indices);

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();

		// Rectangle

		shader->use();
		vao->bind();
		shader->drawElements(6);
		vao->unbind();

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

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);
	}

	delete shader;
	delete vao;
}
