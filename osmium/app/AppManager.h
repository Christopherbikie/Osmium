#pragma once

//#include <GLFW/glfw3.h>
#include "App.h"

namespace os
{
	class AppManager
	{
	public:
		template <typename T>
		static bool init();
		static void deinit();

		static App* instance();

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		static App *appSingleton;

		AppManager();
		AppManager(AppManager const&);
		App& operator=(AppManager const&);
	};

	template <typename T>
	bool AppManager::init()
	{
		if (!appSingleton)
		{
			appSingleton = new T;
			if (!appSingleton->initGL())
			{
				delete appSingleton;
				return false;
			}
		}
		return true;
	}
}
