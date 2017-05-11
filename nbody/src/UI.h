#pragma once

#include <render/scene/SceneManager.h>

namespace ui
{
	struct TimeState
	{
		double_t delta;           // ms
		double_t scaledDelta;     // s
		float_t deltaMultiplier;  // scalar
		bool paused;
		bool reversed;
	};

	void update(std::shared_ptr<os::Scene> scene, TimeState *timeState);
}
