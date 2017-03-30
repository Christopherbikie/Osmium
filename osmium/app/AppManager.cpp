#include "AppManager.h"
#include "Settings.h"

namespace os
{
	App* AppManager::appSingleton = nullptr;

	void AppManager::deinit()
	{
		delete appSingleton;
	}

	App* AppManager::instance()
	{
		return appSingleton;
	}

	AppManager::AppManager()
	{
	}

	void AppManager::framebufferSizeCallback(GLFWwindow *window, int width, int height)
	{
		if (window == appSingleton->getWindow())
			settings::setViewport(glm::vec2(width, height));
	}
}
