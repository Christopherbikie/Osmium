#pragma once

#include "../Entity.h"
#include <memory>

namespace os
{
	class BaseComponent
	{
	private:
		std::shared_ptr<Entity> parent;
	
	public:
		void SetParent(Entity& parent);
		std::shared_ptr<Entity> GetParent();
	};
}