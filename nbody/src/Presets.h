#pragma once

#include <render/scene/SceneManager.h>

namespace presets
{
	const double_t earthMass = 5.97219e24;
	const double_t earthRadius = 6'371'000;
	const double_t moonMass = 7.34767309e22;
	const double_t moonRadius = 1'737'000;
	const double_t earthMoonDistance = 3.85e8;
	const double_t sunMass = 1.989e30;
	const double_t sunRadius = 6.957e8;
	const double_t sunEarthDistance = 1.49598023e11;

	std::shared_ptr<os::Scene> earthMoonSystem(int32_t gravityExponent);
	std::shared_ptr<os::Scene> sunEarthMoonSystem(int32_t gravityExponent);
	std::shared_ptr<os::Scene> twoEarthSystem(int32_t gravityExponent);
}
