#include <string>
#include <memory>
#include <unordered_map>
#include <ctype.h>

namespace os {
	class BaseComponent;

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

	private:
		bool markedForDelete = false;
		componentMap components;
	};
}