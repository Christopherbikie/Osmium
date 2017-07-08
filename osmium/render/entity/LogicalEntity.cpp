#include "LogicalEntity.h"

// Include Components
#include "components/BaseComponent.h"


namespace os
{
	void LogicalEntity::addComponent(std::string componentIdentifier, std::shared_ptr<BaseComponent> componentPtr)
	{
		this->components.insert(std::pair<std::string, std::shared_ptr<BaseComponent>>(componentIdentifier, componentPtr));
		componentPtr->setParent(this);
	}

	void LogicalEntity::removeComponent(const std::string& componentIdentifier)
	{
		this->components.erase(componentIdentifier);
	}

	std::shared_ptr<BaseComponent> LogicalEntity::getComponent(const std::string& componentIdentifier)
	{
		auto t = components.find(componentIdentifier);
		if (t == components.end())
			return nullptr;
		return t->second;
	}

	void LogicalEntity::remove()
	{
		this->markedForDelete = true;
	}

	bool LogicalEntity::shouldRemove()
	{
		return this->markedForDelete;
	}
}