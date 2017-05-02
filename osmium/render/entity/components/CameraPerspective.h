#pragma once

#include "Camera.h"

namespace os
{
	class CameraPerspective : public Camera
	{
	public:
		CameraPerspective(float_t fov, float_t aspectRatio, float_t near, float_t far);

		float_t getFov() const;
		void setFov(float_t fov);

		float_t getAspectRatio() const;
		void setAspectRatio(float_t aspectRatio);

	private:
		glm::mat4 calculateMatrix() override;

		float_t mFOV;
		float_t mAspectRatio;
	};
}
