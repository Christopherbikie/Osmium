#include "TestApp.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <render/entity/components/CameraPerspective.h>
#include <input/Mouse.h>
#include <render/mesh/Mesh.h>
#include <app/Settings.h>
#include "render/entity/components/PointLight.h"


using namespace os;

void TestApp::run()
{
	auto test = Mesh("res/models/sponza.obj");

	shader = new os::Shader;
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	world = Scene();
	Entity ent = *world.addEntity();
	mainCamera = world.addEntity("camera");

	std::shared_ptr<Transform<3, double_t>> transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
	ent.addComponent("Transform", transform);

    transform->setScale(glm::vec3(0.01f));
	auto cameraTransform = std::shared_ptr<Transform<3, float_t>>(new Transform<3, float_t>());
	auto camera = std::shared_ptr<CameraPerspective>(new CameraPerspective(cameraTransform, 60.0f, settings::getAspectRatio(), 0.3f, 100.0f));
	auto control = std::shared_ptr<PlayerControlFPV>(new PlayerControlFPV(cameraTransform));
	auto light = std::shared_ptr<PointLightComponent>(new PointLightComponent());
	light->setIntensity(1.0f);
	light->setColor(1.0f, 1.0f, 1.0f);

	light->setLinear(0.14);
	light->setQuadratic(0.07);

	mainCamera->addComponent("Transform", cameraTransform);
	mainCamera->addComponent("Camera", camera);
	mainCamera->addComponent("Control", control);
	mainCamera->addComponent("PointLight", light);

	//camera = new CameraPerspective(60.0f, settings::getAspectRatio(), 0.3f, 100.0f);                 // Perspective camera
//	camera = new CameraOrthographic(glm::vec2(0.0), settings::getViewport() / 100.0f, 0.3f, 100.0f); // Orthographic camera

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);

	uint64_t frameNum = 0;
	glm::vec2 prevMouseV = glm::vec2(0.0f);

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		control->update((float_t) delta);

		// Cube

		shader->use();

		double_t time = glfwGetTime();
//		transform->setPosition(glm::dvec3(sin(time), 0.0f, 0.0f));
//		transform->setRotation(glm::dvec3(0.0, time, sin(time)));
		//transform->setScale(glm::dvec3(sin(time * 2.0), sin(time * 3.0), sin(time * 4.0)));

		shader->loadUniform("model", transform->getMatrix());
		shader->loadUniform("view", camera->getViewMatrix());
		shader->loadUniform("projection", camera->getProjMatrix());

		//texture->bind(shader, "diffuse");
		glFrontFace(GL_CCW);
		light->loadUniforms(shader);
		test.draw(shader);
		//texture->unbind();

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

		glm::vec3 temp = transform->getPosition(); // must create variable for this one because we have to cast to fvec3
		ImGui::InputFloat3("Cube position", (GLfloat *) &temp);

		temp = cameraTransform->getPosition();
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
		{
			os::reloadShaders();
		}

		ImGui::End();

		ImGui::Render();

		// Swap buffers

		glfwSwapBuffers(mWindow);

		frameNum++;
	}

	delete shader;
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
