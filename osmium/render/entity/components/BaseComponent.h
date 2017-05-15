#pragma once
#include <memory>

namespace os {
	class LogicalEntity;

	class BaseComponent
	{
	private:
		std::shared_ptr<LogicalEntity> parent;
	public:
		void setParent(LogicalEntity& parent);
		std::shared_ptr<LogicalEntity> getParent();
	};
}
