#include <string>
#include <memory>
#include <unordered_map>
#include <ctype.h>

// Include Components
#include "components/BaseComponent.h"

// Include Messages
#include "messages/Message.h"


namespace os {
	typedef std::shared_ptr<BaseComponent> componentPtr;
	typedef std::unordered_map<std::string, std::shared_ptr<BaseComponent>> componentMap;

	class LogicalEntity {
	public:
		void addComponent(std::string, componentPtr);
		void removeComponent(const std::string& componentIdentifier);
		void removeAllComponents();

		std::shared_ptr<BaseComponent> getComponent(const std::string& componentIdentifier);
		
		void remove();
		bool shouldRemove();

		template <class T>
		inline void DispatchMessage(T message) {
			for (auto& i : components) {
				i.second->receiveMessage(message);
			}
		}
	private:
		bool markedForDelete = false;
		componentMap components;
	};
}