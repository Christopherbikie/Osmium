#include "BaseComponent.h"
#include "../LogicalEntity.h"

namespace os
{
	void BaseComponent::setParent(LogicalEntity *parent)
	{
		this->mParent = parent;
	}

	std::shared_ptr<LogicalEntity> BaseComponent::getParent()
	{
		return std::make_shared<LogicalEntity>(*this->mParent);
	}
}
