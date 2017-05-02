#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <util/GLMHelpers.h>
#include "Physics.h"

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;
using namespace glm;

const double_t earthMass = 5.97219e24;
const double_t earthRadius = 6'371'000;
const double_t moonMass = 7.34767309e22;
const double_t moonOrbitalRadius = 3.85e8;

struct object
{
	dvec2 position;
	dvec2 velocity;
	double_t mass;

	dvec2 force;
};

// Returns a nonzero value if a key has been pressed.
// Otherwise, it returns 0.
int kbhit()
{
#ifdef _WIN32
	return _kbhit();
#else
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
#endif
}

int main()
{
	cout << "Hit enter to exit" << endl;

	const double_t deltaT = 10; // seconds

	object earth = { dvec2(0), dvec2(0), earthMass };
	object otherObj = { dvec2(earthRadius, 0), dvec2(0, -physics::getStableOrbitVelocity(earth.mass, earthRadius)), 1000};
	object moon = {dvec2(moonOrbitalRadius, 0), dvec2(0, -physics::getStableOrbitVelocity(earth.mass, moonOrbitalRadius)), moonMass};

	vector<object *> objects = { &earth, &otherObj, &moon };

	while (true)
	{
		// Sum forces for each object
		for (auto i = objects.begin(); i != objects.end(); ++i)
		{
			for (auto j = (i+1); j != objects.end(); ++j)
			{
				object *obj1 = *i;
				object *obj2 = *j;

				dvec2 force = physics::getGravityForce(obj1->mass, obj2->mass, obj1->position, obj2->position);
				obj1->force += force;
				obj2->force -= force;
			}
		}

		// Calculate acceleration, velocity and position for each object then clear force
		for (object *obj : objects)
		{
			dvec2 acceleration = physics::getAcceleration(obj->force, obj->mass);
			obj->velocity = physics::getNextVelocity(deltaT, acceleration, obj->velocity);
			cout << (obj->position = physics::getNextPosition(deltaT, obj->position, obj->velocity)) << endl;
			obj->force = dvec2(0);
		}

		cout << "---" << endl;
		this_thread::sleep_for(100ms);

		// Break if a key is pressed (depending on console may have to press enter)
		if (kbhit()) break;
	}

	return EXIT_SUCCESS;
}
