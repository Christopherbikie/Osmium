#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <ctype.h>

// Include Components
#include "components/BaseComponent.h"

// Include Messages
#include "messages/Message.h"

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
		template <class T>
		void DispatchMessage(T message) {
			for (auto& i : components) {
				i.second->ReceiveMessage(message);
			}
		}
	private:
		bool markedForDelete = false;
		std::unordered_map<std::string, std::shared_ptr<BaseComponent>> components;
	};
}

