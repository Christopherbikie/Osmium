#include "TestApp.h"
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/CameraPerspective.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <input/Mouse.h>
#include <app/Settings.h>
#include <render/mesh/OBJLoader.h>
#include "components/PhysicsComponent.h"
#include "math/Physics.h"

using namespace os;

const double_t earthMass = 5.97219e24;
const double_t earthRadius = 6'371'000;
const double_t moonMass = 7.34767309e22;
const double_t moonRadius = 1'737'000;
const double_t moonOrbitalRadius = 3.85e8;

void TestApp::run()
{
	settings::setWindowTitle("n-body simulation by Chris and Matt");

	glEnable(GL_PROGRAM_POINT_SIZE);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->addSource(VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	auto mesh = OBJLoader::loadOBJ("res/models/sphere.obj");

	scene = Scene();
	cameraEntity = scene.addLogical("Camera");

	auto cameraTransform = std::make_shared<Transform<3, float_t>>(Transform<3, float_t>());
	cameraTransform->setPosition(glm::dvec3(moonOrbitalRadius, 0.0, 0.0));
	auto camera = std::make_shared<CameraPerspective>(CameraPerspective(cameraTransform, 60.0f, settings::getAspectRatio(), 10000.0f, 10'000'000'000.0f));
	auto control = std::make_shared<PlayerControlFPV>(PlayerControlFPV(cameraTransform));
	control->setMoveSpeed(50000000.0f);

	cameraEntity->addComponent("Transform", cameraTransform);
	cameraEntity->addComponent("Camera", camera);
	cameraEntity->addComponent("Control", control);

	{
		auto entity = scene.addEntity("earth");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		transform->setPosition(glm::dvec3(0.0));
		transform->setScale(glm::vec3(earthRadius));
		entity->addComponent("Transform", transform);

		auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, earthMass);
		entity->addComponent("Physics", physics);
	}

	{
		auto entity = scene.addEntity("Moon");

		auto transform = std::make_shared<Transform<3, double_t>>(Transform<3, double_t>());
		transform->setPosition(glm::dvec3(moonOrbitalRadius, 0.0, 0.0));
		transform->setScale(glm::vec3(moonRadius));
		entity->addComponent("Transform", transform);

		auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, moonMass);
		physics->setVelocity(glm::dvec3(0.0, 0.0, physics::getStableOrbitVelocity(earthMass, moonOrbitalRadius)));
		entity->addComponent("Physics", physics);
	}

	// Get list of entities to apply physics operations to
	std::vector<std::shared_ptr<Entity>> physicsEnts;
	for (worldEnt ent : scene.getWorldEnts())
		if (std::get<1>(ent)->getComponent("Physics") != nullptr)
			physicsEnts.push_back(std::get<1>(ent));

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);
	
	float_t deltaMultiplier = 1.0f;

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		double_t delta = 1000.0f / ImGui::GetIO().Framerate;

		control->update((float_t) delta);
		
		double_t scaledDelta = delta * deltaMultiplier / 1000.0;

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
			phys->setVelocity(physics::getNextVelocity(scaledDelta, acceleration, phys->getVelocity()));
			trans->setPosition(physics::getNextPosition(scaledDelta, trans->getPosition(), phys->getVelocity()));
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
			mesh->draw(shader.get());
		}

		// GUI

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", delta, ImGui::GetIO().Framerate);

		glm::vec3 temp = cameraTransform->getPosition();
		ImGui::InputFloat3("Camera position", (GLfloat *) &temp);
		cameraTransform->setPosition(temp);
		temp = cameraTransform->getRotation();
		ImGui::InputFloat3("Camera rotation", (GLfloat *) &temp);
		cameraTransform->setRotation(temp);

		ImGui::Text("Scaled delta: %.3f", scaledDelta);
		ImGui::InputFloat("Speed sec/sec", &deltaMultiplier);

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
