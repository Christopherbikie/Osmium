#include <render/entity/components/MeshComponent.h>
#include "Presets.h"
#include "components/PathComponent.h"
#include "components/PhysicsComponent.h"
#include "math/Physics.h"

namespace presets
{
	std::shared_ptr<os::Scene> earthMoonSystem(int32_t gravityExponent)
	{
		auto scene = std::make_shared<os::Scene>();

		{
			auto entity = scene->addEntity("Earth");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(-physics::getBarycenterDist(earthMoonDistance, earthMass, moonMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) earthRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, earthMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0, -physics::getStableOrbitVelocityNew(earthMass, moonMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/earth.obj");
			entity->addComponent("Mesh", mesh);
		}

		{
			auto entity = scene->addEntity("Moon");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(physics::getBarycenterDist(earthMoonDistance, moonMass, earthMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) moonRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, moonMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0, physics::getStableOrbitVelocityNew(moonMass, earthMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/moon.obj");
			entity->addComponent("Mesh", mesh);
		}

		return scene;
	}

	std::shared_ptr<os::Scene> sunEarthMoonSystem(int32_t gravityExponent)
	{
		auto scene = std::make_shared<os::Scene>();

		{
			auto entity = scene->addEntity("Sun");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(-physics::getBarycenterDist(sunEarthDistance, sunMass, earthMass + moonMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) sunRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, sunMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0, -physics::getStableOrbitVelocityNew(sunMass, earthMass + moonMass, sunEarthDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/sun.obj");
			entity->addComponent("Mesh", mesh);
		}

		{
			auto entity = scene->addEntity("Earth");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(
					physics::getBarycenterDist(sunEarthDistance, earthMass, sunMass)
					- physics::getBarycenterDist(earthMoonDistance, earthMass, moonMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) earthRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, earthMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0,
					physics::getStableOrbitVelocityNew(earthMass, sunMass, sunEarthDistance)
					- physics::getStableOrbitVelocityNew(earthMass, moonMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/earth.obj");
			entity->addComponent("Mesh", mesh);
		}

		{
			auto entity = scene->addEntity("Moon");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(
					physics::getBarycenterDist(sunEarthDistance, earthMass, sunMass)
					+ physics::getBarycenterDist(earthMoonDistance, moonMass, earthMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) moonRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, moonMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0,
					physics::getStableOrbitVelocityNew(earthMass, sunMass, sunEarthDistance)
					- physics::getStableOrbitVelocityNew(earthMass, moonMass, earthMoonDistance, gravityExponent)
					+ physics::getStableOrbitVelocityNew(moonMass, earthMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/moon.obj");
			entity->addComponent("Mesh", mesh);
		}

		return scene;
	}

	std::shared_ptr<os::Scene> twoEarthSystem(int32_t gravityExponent)
	{
		auto scene = std::make_shared<os::Scene>();

		{
			auto entity = scene->addEntity("Earth1");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(physics::getBarycenterDist(earthMoonDistance, earthMass, earthMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) earthRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, earthMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0, -physics::getStableOrbitVelocityNew(earthMass, earthMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/earth.obj");
			entity->addComponent("Mesh", mesh);
		}

		{
			auto entity = scene->addEntity("Earth2");

			auto transform = std::make_shared<os::Transform<3, double_t>>(os::Transform<3, double_t>());
			transform->setPosition(glm::dvec3(-physics::getBarycenterDist(earthMoonDistance, earthMass, earthMass), 0.0, 0.0));
			transform->setScale(glm::vec3((float) earthRadius));
			entity->addComponent("Transform", transform);

			auto physics = std::make_shared<PhysicsComponent<3, double_t>>(transform, earthMass);
			physics->setVelocity(glm::dvec3(0.0, 0.0, physics::getStableOrbitVelocityNew(earthMass, earthMass, earthMoonDistance, gravityExponent)));
			entity->addComponent("Physics", physics);

			auto path = std::make_shared<PathComponent<3, double_t>>(transform);
			entity->addComponent("Path", path);

			auto mesh = std::make_shared<os::MeshComponent>("res/models/earth.obj");
			entity->addComponent("Mesh", mesh);
		}

		return scene;
	}
}
