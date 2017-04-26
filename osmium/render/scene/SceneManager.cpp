#include "SceneManager.h"

namespace os {
	entityList& Scene::getEntities() {
		return this->entities;
	}
	entityList::iterator Scene::addEntity(Entity& ent, std::string entId)
	{
		entityList::iterator endIterator = this->entities.end();
		this->entities.push_back(entityContainer(entId, std::make_shared<Entity>(ent)));
		return endIterator
	}
	void Scene::removeEntity(entityList::iterator entIdentifier) {
		this->entities.erase(entIdentifier);
	}
	void Scene::removeEntity(std::shared_ptr<Entity> ent) {
		for (auto k : this->entities) {

		}
	}
}