#include "BaseComponent.h"

namespace os
{

	void BaseComponent::SetParent(Entity& parent)
	{
		this->parent = std::make_shared<Entity>(parent);
	}

	std::shared_ptr<Entity> BaseComponent::GetParent()
	{
		return this->parent;
	}
}