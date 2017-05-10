#include "TestApp.h"
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/CameraPerspective.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <input/Mouse.h>
#include <app/Settings.h>
#include "components/PhysicsComponent.h"
#include "math/Physics.h"

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

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, 10);
			entity->addComponent("Physics", physics);
		}

	// Get list of entities to apply physics operations to
	std::vector<std::shared_ptr<Entity>> physicsEnts;
	for (worldEnt ent : scene.getWorldEnts())
		if (std::get<1>(ent)->getComponent("Physics") != nullptr)
			physicsEnts.push_back(std::get<1>(ent));

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		control->update((float_t) delta);

		// Do physics

		// Set all forces to 0
		for (auto &&ent : physicsEnts)
			std::static_pointer_cast<PhysicsComponent<3, double_t>>(ent->getComponent("Physics"))->setForce(glm::dvec3(0));

		// Sum forces for each entity
		for (auto i = physicsEnts.begin(); i != physicsEnts.end(); ++i)
		{
			for (auto j = (i + 1); j != physicsEnts.end(); ++j)
			{
				std::shared_ptr<Entity> ent1 = *i;
				auto phys1 = std::static_pointer_cast<PhysicsComponent<3, double_t>>(ent1->getComponent("Physics"));
				auto trans1 = std::static_pointer_cast<Transform<3, double_t>>(ent1->getComponent("Transform"));

				std::shared_ptr<Entity> ent2 = *j;
				auto phys2 = std::static_pointer_cast<PhysicsComponent<3, double_t>>(ent2->getComponent("Physics"));
				auto trans2 = std::static_pointer_cast<Transform<3, double_t>>(ent2->getComponent("Transform"));

				glm::dvec3 force = physics::getGravityForce(phys1->getMass(), phys2->getMass(), trans1->getPosition(), trans2->getPosition());
				phys1->getForce() += force;
				phys2->getForce() -= force;
			}
		}

		// Calculate acceleration, velocity and position for each entity
		for (auto &&ent : physicsEnts)
		{
			auto phys = std::static_pointer_cast<PhysicsComponent<3, double_t>>(ent->getComponent("Physics"));
			auto trans = std::static_pointer_cast<Transform<3, double_t>>(ent->getComponent("Transform"));

			glm::dvec3 acceleration = physics::getAcceleration(phys->getForce(), phys->getMass());
			phys->setVelocity(physics::getNextVelocity(delta, acceleration, phys->getVelocity()));
			trans->setPosition(physics::getNextPosition(delta, trans->getPosition(), phys->getVelocity()));
		}

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
