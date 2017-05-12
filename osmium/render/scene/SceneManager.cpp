#include "SceneManager.h"

namespace os
{
	std::shared_ptr<Entity> Scene::addEntity(std::string tag)
	{
		std::shared_ptr<Entity> vecptr = std::make_shared<Entity>();
		std::shared_ptr<Entity> returnptr = vecptr;

		this->worldEnts.push_back(worldEnt(tag, vecptr));

		return returnptr;
	}

	std::shared_ptr<LogicalEntity> Scene::addLogical(std::string tag)
	{
		std::shared_ptr<LogicalEntity> vecptr = std::make_shared<LogicalEntity>();
		std::shared_ptr<LogicalEntity> returnptr = vecptr;

		this->logicalEnts.push_back(logicEnt(tag, vecptr));

		return returnptr;
	}

	worldList Scene::getWorldEnts()
	{
		return worldEnts;
	}

	logicalList Scene::getLogicalEnts()
	{
		return logicalEnts;
	}
}
