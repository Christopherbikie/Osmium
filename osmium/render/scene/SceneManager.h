#pragma once

#include "../entity/Entity.h"

#include <vector>
#include <memory>
#include <tuple>
#include <cctype>
#include <string>

typedef std::tuple<std::string, std::shared_ptr<os::LogicalEntity>> logicEnt;
typedef std::tuple<std::string, std::shared_ptr<os::Entity>> worldEnt;

typedef std::vector<logicEnt> logicalList;
typedef std::vector<worldEnt> worldList;

namespace os
{
	class Scene
	{
	public:
		virtual std::shared_ptr<Entity> addEntity(std::string tag = "");
		virtual std::shared_ptr<LogicalEntity> addLogical(std::string tag = "");

		virtual worldList getWorldEnts();
		virtual logicalList getLogicalEnts();

	private:
		worldList worldEnts;
		logicalList logicalEnts;
	};
}