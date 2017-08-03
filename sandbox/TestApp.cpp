#include "TestApp.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <render/entity/components/CameraPerspective.h>
#include <input/Mouse.h>
#include <render/mesh/Mesh.h>
#include <app/Settings.h>
#include <assets/TextureStore.h>
#include <render/entity/components/MeshComponent.h>
#include "render/entity/components/PointLight.h"


using namespace os;

void TestApp::run()
{
	shader = std::make_shared<os::Shader>();
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	world = Scene();

	{
		mainCamera = world.addLogical("Camera");

		auto transform = std::shared_ptr<Transform<3, float_t>>(new Transform<3, float_t>());
		auto camera = std::shared_ptr<CameraPerspective>(new CameraPerspective(transform, 60.0f, settings::getAspectRatio(), 0.3f, 100.0f));
		auto control = std::shared_ptr<PlayerControlFPV>(new PlayerControlFPV(transform));
		auto light = std::shared_ptr<PointLightComponent>(new PointLightComponent());
		light->setIntensity(1.0f);
		light->setColor(1.0f, 1.0f, 1.0f);

		light->setLinear(0.14);
		light->setQuadratic(0.07);

		mainCamera->addComponent("Transform", transform);
		mainCamera->addComponent("Camera", camera);
		mainCamera->addComponent("Control", control);
		mainCamera->addComponent("Light", light);
	}

	{
		auto sponza = world.addEntity("sponza");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		transform->setScale(glm::vec3(0.01f));
		sponza->addComponent("Transform", transform);

		auto mesh = std::make_shared<MeshComponent>("res/models/sponza.obj");
		sponza->addComponent("Mesh", mesh);
	}

	{
		auto cube = world.addEntity("cube");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		cube->addComponent("Transform", transform);

		auto mesh = std::make_shared<MeshComponent>("res/models/cube.obj");
		cube->addComponent("Mesh", mesh);
	}

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);

	uint64_t frameNum = 0;
	glm::vec2 prevMouseV = glm::vec2(0.0f);

	bool showTextureStoreWindow = false;

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		std::static_pointer_cast<PlayerControlFPV>(mainCamera->getComponent("Control"))->update((float_t) delta);

		// Cube

		shader->use();

		double_t time = glfwGetTime();

		auto camera = std::static_pointer_cast<CameraPerspective>(mainCamera->getComponent("Camera"));
		shader->loadUniform("view", camera->getViewMatrix());
		shader->loadUniform("projection", camera->getProjMatrix());

		std::static_pointer_cast<PointLightComponent>(mainCamera->getComponent("Light"))->loadUniforms(shader);

		for (worldEnt ent : world.getWorldEnts())
		{
			if (std::get<0>(ent) == "Camera")
				continue;
			auto transform = std::static_pointer_cast<Transform<3, double_t>>(std::get<1>(ent)->getComponent("Transform"));
			shader->loadUniform("model", transform->getMatrix());
			std::static_pointer_cast<MeshComponent>(std::get<1>(ent)->getComponent("Mesh"))->draw(shader);
		}

		// GUI

		ImGui::Begin("Debug");

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

		auto cameraTransform = std::static_pointer_cast<os::Transform<3, float_t>>(mainCamera->getComponent("Transform"));

		glm::vec3 temp = cameraTransform->getPosition();
		ImGui::InputFloat3("Camera position", (GLfloat *) &temp);
		cameraTransform->setPosition(temp);
		temp = cameraTransform->getRotation();
		ImGui::InputFloat3("Camera rotation", (GLfloat *) &temp);
		cameraTransform->setRotation(temp);

		ImGui::InputInt2("Mouse position", (GLint *) &mouse::getPosition());
		if (frameNum % 2 == 0)
			prevMouseV = (glm::dvec2) mouse::getMovement() * 1000.0 / delta;
		ImGui::InputFloat2("Mouse velocity (pix/sec)", (GLfloat *) &prevMouseV);

		if (ImGui::Button("Reload Shaders"))
			os::reloadShaders();

		ImGui::SameLine();
		if (ImGui::Button("Toggle texture window"))
			showTextureStoreWindow = !showTextureStoreWindow;

		ImGui::End();

		if (showTextureStoreWindow)
			textureStore::showDebugWindow();

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);

		frameNum++;
	}
}

void TestApp::windowResizeCallback(glm::vec2 dimensions)
{
	std::shared_ptr<CameraPerspective> camera = std::static_pointer_cast<CameraPerspective>(mainCamera->getComponent("Camera"));
	camera->setAspectRatio(settings::getAspectRatio());
}

void TestApp::pressKey(uint32_t key)
{
	if (key == GLFW_KEY_ESCAPE)
		mouse::toggleCaptured();
}
