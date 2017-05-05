#include <glad/glad.h>
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
		{
			glViewport(0, 0, width, height);
			glm::vec2 dimensions = glm::vec2(width, height);
			settings::setViewport(dimensions);
			appSingleton->windowResizeCallback(dimensions);
		}
	}
}
