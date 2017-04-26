#pragma once

#include <memory>
#include "../messages/Message.h"

namespace os {
	class Entity;

	class BaseComponent
	{
	private:
		std::shared_ptr<Entity> parent;
	public:
		void setParent(Entity& parent);
		std::shared_ptr<Entity> getParent();
		void ReceiveMessage(BaseMessage);
		void ReceiveMessage(NewComponent);
	};
}