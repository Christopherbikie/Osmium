#pragma once

class GLFWwindow;

namespace os
{
	class App
	{
	public:
		App();
		~App();

		bool initGL();
		virtual bool init();
		virtual void run() = 0;

		GLFWwindow* getWindow();

	protected:
		GLFWwindow *mWindow;

	private:
		bool mInitialised;
	};
}
