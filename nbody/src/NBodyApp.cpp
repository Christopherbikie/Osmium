#include "NBodyApp.h"
#include <imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <render/entity/components/CameraPerspective.h>
#include <render/entity/components/PlayerControlFPV.h>
#include <app/Settings.h>
#include <render/entity/components/MeshComponent.h>
#include "components/PathComponent.h"
#include "components/PhysicsComponent.h"
#include "math/Physics.h"
#include "UI.h"
#include "Presets.h"

using namespace os;

void NBodyApp::run()
{
	settings::setWindowTitle("n-body simulation by Chris and Matt");
	settings::setClearColour(glm::vec3(0.0f));
	setWindowSize(glm::ivec2(1600, 900));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::shared_ptr<Shader> entityShader = std::make_shared<Shader>();
	entityShader->addSource(VERTEX_SHADER, "res/shaders/entity.vert");
	entityShader->addSource(FRAGMENT_SHADER, "res/shaders/entity.frag");
	entityShader->link();

	std::shared_ptr<Shader> pathShader = std::make_shared<Shader>();
	pathShader->addSource(VERTEX_SHADER, "res/shaders/path.vert");
	pathShader->addSource(FRAGMENT_SHADER, "res/shaders/path.frag");
	pathShader->link();

	int32_t exp = -2;
	scene = presets::earthMoonSystem(exp);

	{
		cameraEntity = scene->addLogical("Camera");

		auto cameraTransform = std::make_shared<Transform<3, float_t>>(Transform<3, float_t>());
		cameraTransform->setPosition(glm::dvec3(0.0, 0.0, presets::earthMoonDistance));
		auto camera = std::make_shared<CameraPerspective>(CameraPerspective(cameraTransform, 60.0f, settings::getAspectRatio(), 10000.0f, 1000'000'000'000.0f));
		auto control = std::make_shared<PlayerControlFPV>(PlayerControlFPV(cameraTransform));
		control->setMoveSpeed(50000000.0f);

		cameraEntity->addComponent("Transform", cameraTransform);
		cameraEntity->addComponent("Camera", camera);
		cameraEntity->addComponent("Control", control);
	}

	// Get list of entities to apply physics operations to
	std::vector<std::shared_ptr<Entity>> physicsEnts;
	for (worldEnt ent : scene->getWorldEnts())
		if (std::get<1>(ent)->getComponent<PhysicsComponent<3, double_t>>("Physics") != nullptr)
			physicsEnts.push_back(std::get<1>(ent));

	keyboard::addKeyHandler(GLFW_KEY_ESCAPE, this);
	mouse::addScrollHandler(this);

	ui::TimeState timeState;
	timeState.deltaMultiplier = 1.0f;
	timeState.paused = false;
	timeState.reversed = false;

	while (!glfwWindowShouldClose(mWindow))
	{
		newFrame();
		timeState.delta = 1000.0f / ImGui::GetIO().Framerate;
		timeState.scaledDelta = timeState.paused ? 0.0 : timeState.delta * timeState.deltaMultiplier / 1000.0;
		if (timeState.reversed) timeState.scaledDelta *= -1;

		auto control = cameraEntity->getComponent<PlayerControlFPV>("Control");
		control->update((float_t) timeState.delta);

		// Do physics

		// Set all forces to 0
		for (auto &&ent : physicsEnts)
			ent->getComponent<PhysicsComponent<3, double_t>>("Physics")->setForce(glm::dvec3(0));

		// Sum forces for each entity
		for (auto i = physicsEnts.begin(); i != physicsEnts.end(); ++i)
		{
			for (auto j = (i + 1); j != physicsEnts.end(); ++j)
			{
				std::shared_ptr<Entity> ent1 = *i;
				auto phys1 = ent1->getComponent<PhysicsComponent<3, double_t>>("Physics");
				auto trans1 = ent1->getComponent<Transform<3, double_t>>("Transform");

				std::shared_ptr<Entity> ent2 = *j;
				auto phys2 = ent2->getComponent<PhysicsComponent<3, double_t>>("Physics");
				auto trans2 = ent2->getComponent<Transform<3, double_t>>("Transform");

				glm::dvec3 force = physics::getGravityForce(phys1->getMass(), phys2->getMass(), trans1->getPosition(), trans2->getPosition(), exp);
				phys1->getForce() += force;
				phys2->getForce() -= force;
			}
		}

		// Calculate acceleration, velocity and position for each entity
		for (auto &&ent : physicsEnts)
		{
			auto phys = ent->getComponent<PhysicsComponent<3, double_t>>("Physics");
			auto trans = ent->getComponent<Transform<3, double_t>>("Transform");

			glm::dvec3 acceleration = physics::getAcceleration(phys->getForce(), phys->getMass());
			phys->setAcceleration(acceleration); // Not used for calculations, just saved to be displayed to user
			phys->setVelocity(physics::getNextVelocity(timeState.scaledDelta, acceleration, phys->getVelocity()));
			trans->setPosition(physics::getNextPosition(timeState.scaledDelta, trans->getPosition(), phys->getVelocity()));
		}

		// Render entities

		entityShader->use();
		auto camera = cameraEntity->getComponent<CameraPerspective>("Camera");
		entityShader->loadUniform("view", camera->getViewMatrix());
		entityShader->loadUniform("projection", camera->getProjMatrix());

		for (worldEnt ent : scene->getWorldEnts())
		{
			if (std::get<0>(ent) == "Camera")
				continue;
			auto transform = std::get<1>(ent)->getComponent<Transform<3, double_t>>("Transform");
			transform->loadMatrices(entityShader);
			std::get<1>(ent)->getComponent<MeshComponent>("Mesh")->draw(entityShader);
		}

		// Render paths / trails

		pathShader->use();
		pathShader->loadUniform("view", camera->getViewMatrix());
		pathShader->loadUniform("projection", camera->getProjMatrix());

		for (worldEnt ent : scene->getWorldEnts())
		{
			auto path = std::get<1>(ent)->getComponent<PathComponent<3, double_t>>("Path");
			if (path == nullptr) continue;
			path->updatePath();
			path->renderPath(pathShader);
		}

		// GUI
		ui::update(scene, &timeState, &exp);

		// Swap buffers
		glfwSwapBuffers(mWindow);
	}
}

void NBodyApp::windowResizeCallback(glm::vec2 dimensions)
{
	auto camera = cameraEntity->getComponent<CameraPerspective>("Camera");
	camera->setAspectRatio(settings::getAspectRatio());
}

void NBodyApp::pressKey(uint32_t key)
{
	if (key == GLFW_KEY_ESCAPE)
		mouse::toggleCaptured();
}

void NBodyApp::scroll(glm::ivec2 offset)
{
	auto control = cameraEntity->getComponent<PlayerControlFPV>("Control");
	control->setMoveSpeed(control->getMoveSpeed() + control->getMoveSpeed() * 0.2f * offset.y);
}
