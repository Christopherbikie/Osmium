#pragma once

#include <memory>
#include "../messages/Message.h"

namespace os {
	class LogicalEntity;

	class BaseComponent
	{
	private:
		std::shared_ptr<LogicalEntity> parent;
	public:
		void setParent(LogicalEntity& parent);
		std::shared_ptr<LogicalEntity> getParent();
		void receiveMessage(BaseMessage);
	};
}