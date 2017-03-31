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
		virtual void run() = 0;

		GLFWwindow* getWindow();

	protected:
		GLFWwindow *mWindow;

		void newFrame();

	private:
		bool mInitialised;
	};
}
