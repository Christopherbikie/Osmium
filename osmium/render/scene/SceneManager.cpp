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
		LogicalEntity ent;

		this->logicalEnts.push_back(logicEnt(tag, std::make_shared<LogicalEntity>(ent)));

		return std::make_shared<LogicalEntity>(ent);
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
