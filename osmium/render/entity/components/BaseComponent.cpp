#include "BaseComponent.h"
#include "../LogicalEntity.h"


namespace os
{

	void BaseComponent::setParent(LogicalEntity& parent)
	{
		this->parent = std::make_shared<LogicalEntity>(parent);
	}

	std::shared_ptr<LogicalEntity> BaseComponent::getParent()
	{
		return this->parent;
	}

	void BaseComponent::ReceiveMessage(BaseMessage message) {

	}

	void BaseComponent::ReceiveMessage(NewComponent message) {

	}
}
