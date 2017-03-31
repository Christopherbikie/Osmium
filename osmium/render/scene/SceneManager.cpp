#include "SceneManager.h"

namespace os {
	entityList& Scene::getEntities() {
		return this->entities;
	}
	void Scene::addEntity(Entity& ent, std::string entId)
	{
		this->entities.push_back(entityContainer(entId, std::make_shared<Entity>(ent)));
	}
	void Scene::removeEntity(int32_t entIdentifier) {

	}
}