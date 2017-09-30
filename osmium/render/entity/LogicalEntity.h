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
		template<typename T>
		std::shared_ptr<T> getComponent(const std::string& componentIdentifier)
		{
			auto t = components.find(componentIdentifier);
			if (t == components.end())
				return nullptr;
			return std::static_pointer_cast<T>(t->second);
		}
		
		void remove();
		bool shouldRemove();

	private:
		bool markedForDelete = false;
		componentMap components;
	};
}