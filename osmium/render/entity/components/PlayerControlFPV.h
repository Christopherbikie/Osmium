#pragma once

#include <memory>
#include <cmath>
#include "Transform.h"

namespace os
{
	class PlayerControlFPV : public BaseComponent
	{
	public:
		PlayerControlFPV(std::shared_ptr<Transform<3, float_t>> transform);

		void update(float_t delta);

	private:
		std::shared_ptr<Transform<3, float_t>> mTransform;
		float_t mMoveSpeed;
		float_t mSensitivity;
	};
}
