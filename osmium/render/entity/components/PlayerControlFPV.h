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

		float_t getMoveSpeed() const;
		float_t getSensitivity() const;

		void setMoveSpeed(float_t mMoveSpeed);
		void setSensitivity(float_t mSensitivity);

	private:
		std::shared_ptr<Transform<3, float_t>> mTransform;
		float_t mMoveSpeed;
		float_t mSensitivity;
	};
}
