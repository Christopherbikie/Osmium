#include "TestApp.h"
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/CameraPerspective.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <input/Mouse.h>
#include "app/Settings.h"

using namespace os;

void TestApp::run()
{
	settings::setWindowTitle("n-body simulation by Chris and Matt");

	glEnable(GL_PROGRAM_POINT_SIZE);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	float_t pointVertices[] = {
			0.0f, 0.0f, 0.0f
	};

	std::unique_ptr<VAO> vao = std::make_unique<VAO>();
	vao->storeInBuffer(0, 3, 1, pointVertices);

	scene = Scene();
	cameraEntity = scene.addLogical("Camera");

	auto cameraTransform = std::make_shared<Transform<3, float_t>>(Transform<3, float_t>());
	auto camera = std::make_shared<CameraPerspective>(CameraPerspective(cameraTransform, 60.0f, settings::getAspectRatio(), 0.3f, 100.0f));
	auto control = std::make_shared<PlayerControlFPV>(PlayerControlFPV(cameraTransform));

	cameraEntity->addComponent("Transform", cameraTransform);
	cameraEntity->addComponent("Camera", camera);
	cameraEntity->addComponent("Control", control);

	for (int x = 0; x < 10; x++)
		for (int z = 0; z < 10; z++)
		{
			auto entity = scene.addEntity("ent" + std::to_string(x) + std::to_string(z));
			auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
			transform->setPosition(glm::vec3(x, 0.0f, z));
			entity->addComponent("Transform", transform);
		}

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		float_t delta = 1000.0f / ImGui::GetIO().Framerate;

		control->update(delta);

		// Render dots

		shader->use();
		shader->loadUniform("view", camera->getViewMatrix());
		shader->loadUniform("projection", camera->getProjMatrix());

		for (worldEnt ent : scene.getWorldEnts())
		{
			if (std::get<0>(ent) == "Camera")
				continue;
			auto transform = std::static_pointer_cast<Transform<3, double_t>>(std::get<1>(ent)->getComponent("Transform"));
			shader->loadUniform("model", transform->getMatrix());
			vao->bind();
			shader->drawArrays(0, 1, GL_POINTS);
			vao->unbind();
		}

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

		glm::vec3 temp = cameraTransform->getPosition();
		ImGui::InputFloat3("Camera position", (GLfloat *) &temp);
		cameraTransform->setPosition(temp);
		temp = cameraTransform->getRotation();
		ImGui::InputFloat3("Camera rotation", (GLfloat *) &temp);
		cameraTransform->setRotation(temp);
		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);
	}
}

void TestApp::windowResizeCallback(glm::vec2 dimensions)
{
	std::shared_ptr<CameraPerspective> camera = std::static_pointer_cast<CameraPerspective>(cameraEntity->getComponent("Camera"));
	camera->setAspectRatio(settings::getAspectRatio());
}

void TestApp::pressKey(uint32_t key)
{
	if (key == GLFW_KEY_ESCAPE)
		mouse::toggleCaptured();
}
