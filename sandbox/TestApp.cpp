#include "TestApp.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include "app/Settings.h"

using namespace os;

void TestApp::run()
{
	shader = new os::Shader;
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	float_t vertices[] = {
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
	};
	float_t colours[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
	};
	uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0,
			1, 5, 6,
			6, 2, 1,
			7, 6, 5,
			5, 4, 7,
			4, 0, 3,
			3, 7, 4,
			4, 5, 1,
			1, 0, 4,
			3, 2, 6,
			6, 7, 3,
	};

	vao = new VAO;
	vao->storeInBuffer(0, 3, 8, vertices);
	vao->storeInBuffer(1, 3, 8, colours);
	vao->storeInElementBuffer(36, indices);

	modelMat = glm::rotate(modelMat, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	projectionMat = glm::perspective(glm::radians(60.0f), settings::getAspectRatio(), 0.3f, 100.0f);

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		float_t delta = 1000.0f / ImGui::GetIO().Framerate;

		// Cube

		shader->use();

		modelMat = glm::rotate(modelMat, delta / 200, glm::vec3(0.1f, 0.2f, 0.3f));
		shader->loadUniform("model", modelMat);
		shader->loadUniform("view", viewMat);
		shader->loadUniform("projection", projectionMat);

		vao->bind();
		shader->drawElements(36);
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

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", delta, ImGui::GetIO().Framerate);

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);
	}

	delete shader;
	delete vao;
}

void TestApp::windowResizeCallback(glm::vec2 dimensions)
{
	projectionMat = glm::perspective(glm::radians(60.0f), settings::getAspectRatio(), 0.3f, 100.0f);
}
