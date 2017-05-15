#include <cstdlib>
#include "app/AppManager.h"
#include "NBodyApp.h"

using namespace os;

int main()
{
	if(!AppManager::init<NBodyApp>())
		return EXIT_FAILURE;
	AppManager::instance()->run();
	AppManager::deinit();

	return EXIT_SUCCESS;
}
