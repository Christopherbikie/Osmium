#include "Entity.h"

namespace os {
	void Entity::addComponent(std::string componentIdentifier, std::shared_ptr<BaseComponent> componentPtr)
	{
		this->components.insert(std::pair<std::string, std::shared_ptr<BaseComponent>>(componentIdentifier, componentPtr));
	}

	void Entity::removeComponent(const std::string& componentIdentifier)
	{
		this->components.erase(componentIdentifier);
	}

	std::shared_ptr<BaseComponent> Entity::getComponent(const std::string& componentIdentifier)
	{
		return this->components.at(componentIdentifier);
	}

	Entity::Entity()
	{

	}
}