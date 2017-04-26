#pragma once

#include "render/entity/Entity.h"

#include <vector>
#include <memory>
#include <tuple>
#include <cctype>

typedef std::tuple<std::string, std::shared_ptr<os::Entity>> entityContainer;
typedef std::vector<entityContainer> entityList;

namespace os {

	class Scene {
		entityList entities;
	public:
		entityList &getEntities();
		entityList::iterator addEntity(Entity& ent, std::string entId);
		void removeEntity(entityList::iterator entIdentifier);
		void removeEntity(std::shared_ptr<Entity> ent);
		void removeEntity(std::string entIdentifier);
	};
}