#include <cstdlib>
#include "app/AppManager.h"
#include "TestApp.h"

using namespace os;

int main()
{
	if(!AppManager::init<TestApp>())
		return EXIT_FAILURE;
	AppManager::instance()->run();
	AppManager::deinit();

	return EXIT_SUCCESS;
}
