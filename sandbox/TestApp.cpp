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
#include <render/graphics/Framebuffer.h>
#include "render/entity/components/PointLight.h"


using namespace os;

void TestApp::run()
{
	shader = std::make_shared<os::Shader>();
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	std::shared_ptr<Shader> screenShader = std::make_shared<Shader>();
	screenShader->addSource(VERTEX_SHADER, "res/shaders/quad.vert");
	screenShader->addSource(FRAGMENT_SHADER, "res/shaders/quad.frag");
	screenShader->link();

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
		transform->setPosition(glm::vec3(0, 0, 0.45f));
		transform->setScale(glm::vec3(0.01f));
		sponza->addComponent("Transform", transform);

		auto mesh = std::make_shared<MeshComponent>("res/models/sponza.obj");
		sponza->addComponent("Mesh", mesh);
	}

	{
		auto earth = world.addEntity("earth");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		transform->setPosition(glm::vec3(2, 0, 0));
		earth->addComponent("Transform", transform);

		auto mesh = std::make_shared<MeshComponent>("res/models/earth.obj");
		earth->addComponent("Mesh", mesh);
	}

	{
		auto mitsuba = world.addEntity("mitsuba");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		transform->setPosition(glm::vec3(-3, 0, 0));
		transform->setScale(glm::vec3(0.7f));
		mitsuba->addComponent("Transform", transform);

		auto mesh = std::make_shared<MeshComponent>("res/models/mitsuba-sphere.obj");
		mitsuba->addComponent("Mesh", mesh);
	}

	fb = framebufferManager::createFramebuffer();
	screenTextureIndex = fb->addTextureAttachment();
	fb->addDepthStencilBuffer();
	fb->setClearColour(glm::vec3(1.0f, 0.0f, 0.0f));
	fb->checkComplete();
	fb->bindDefault();

	std::shared_ptr<VAO> quadVAO = std::make_shared<VAO>();
	quadVAO->storeInBuffer(0, 2, 12, quadVertices);
	quadVAO->storeInBuffer(1, 2, 12, quadTexCoords);

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);

	uint64_t frameNum = 0;
	glm::vec2 prevMouseV = glm::vec2(0.0f);

	bool showTextureStoreWindow = false;
	bool showFramebufferWindow = false;

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		std::static_pointer_cast<PlayerControlFPV>(mainCamera->getComponent("Control"))->update((float_t) delta);

		// Render scene to framebuffer

		fb->bind();

		shader->use();

		double_t time = glfwGetTime();

		auto camera = std::static_pointer_cast<CameraPerspective>(mainCamera->getComponent("Camera"));
		camera->loadUniforms(shader);

		std::static_pointer_cast<PointLightComponent>(mainCamera->getComponent("Light"))->loadUniforms(shader);

		for (worldEnt ent : world.getWorldEnts())
		{
			if (std::get<0>(ent) == "Camera")
				continue;
			if (std::get<0>(ent) == "earth")
				std::static_pointer_cast<Transform<3, double_t>>(std::get<1>(ent)->getComponent("Transform"))->setPosition(glm::vec3(sin(glfwGetTime()), 0, 0));
			if (std::get<0>(ent) == "mitsuba")
				std::static_pointer_cast<Transform<3, double_t>>(std::get<1>(ent)->getComponent("Transform"))->setRotation(glm::vec3(0, sin(glfwGetTime()), 0));
			auto transform = std::static_pointer_cast<Transform<3, double_t>>(std::get<1>(ent)->getComponent("Transform"));
			shader->loadUniform("model", transform->getMatrix());
			std::static_pointer_cast<MeshComponent>(std::get<1>(ent)->getComponent("Mesh"))->draw(shader);
		}

		// Render framebuffer to screen

		fb->bindDefault();
		screenShader->use();
		quadVAO->bind();
		fb->getTexture(screenTextureIndex)->bind(screenShader, "screenTexture");
		glDrawArrays(GL_TRIANGLES, 0, 6);

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

		if (ImGui::Button("Toggle texture window"))
			showTextureStoreWindow = !showTextureStoreWindow;
		ImGui::SameLine();
		if (ImGui::Button("Toggle framebuffer window"))
			showFramebufferWindow = !showFramebufferWindow;

		ImGui::End();

		if (showTextureStoreWindow)
			textureStore::showDebugWindow();
		if (showFramebufferWindow)
			framebufferManager::showDebugWindow();

		shader->use();
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
	glm::ivec2 intDimensions((int) dimensions.x, (int) dimensions.y);
	fb->resize(intDimensions);
}

void TestApp::pressKey(uint32_t key)
{
	if (key == GLFW_KEY_ESCAPE)
		mouse::toggleCaptured();
}
