#include "BaseComponent.h"
#include "../Entity.h"


namespace os
{

	void BaseComponent::setParent(Entity& parent)
	{
		this->parent = std::make_shared<Entity>(parent);
	}

	std::shared_ptr<Entity> BaseComponent::getParent()
	{
		return this->parent;
	}

	void BaseComponent::ReceiveMessage(BaseMessage message) {

	}

	void BaseComponent::ReceiveMessage(NewComponent message) {

	}
}
