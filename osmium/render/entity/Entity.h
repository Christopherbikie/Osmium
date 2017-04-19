#pragma once
#include "components/BaseComponent.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <ctype.h>

namespace os {
	class Entity
	{
	public:
		Entity();
		void addComponent(std::string, std::shared_ptr<BaseComponent>);
		void removeComponent(const std::string& componentIdentifier);
		std::shared_ptr<BaseComponent> getComponent(const std::string& componentIdentifier);
		void remove();
		bool isMarkedForRemoval();
	private:
		bool markedForDelete = false;
		std::unordered_map<std::string, std::shared_ptr<BaseComponent>> components;
	};
}
