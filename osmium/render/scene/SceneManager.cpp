#include "SceneManager.h"

std::shared_ptr<os::Entity> os::Scene::addEntity(std::string tag) {
	os::Entity ent;

	this->World.push_back(worldEnt(tag, std::make_shared<os::Entity>(ent)));

	return std::make_shared<os::Entity>(ent);
}

std::shared_ptr<os::LogicalEntity> os::Scene::addLogical(std::string tag) {
	os::LogicalEntity ent;

	this->Logic.push_back(logicEnt(tag, std::make_shared<os::LogicalEntity>(ent)));

	return std::make_shared<os::LogicalEntity>(ent);
}