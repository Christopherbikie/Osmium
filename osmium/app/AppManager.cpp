#include "AppManager.h"

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
}
