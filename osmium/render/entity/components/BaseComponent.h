#pragma once
#include <memory>

namespace os {
	class LogicalEntity;

	class BaseComponent
	{
	private:
		LogicalEntity *mParent;
	public:
		void setParent(LogicalEntity *parent);
		std::shared_ptr<LogicalEntity> getParent();
	};
}
