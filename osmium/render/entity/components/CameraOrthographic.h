#pragma once

#include "Camera.h"

namespace os
{
	class CameraOrthographic : public Camera
	{
	public:
		// Origin is top left corner
		CameraOrthographic(std::shared_ptr<Transform<3, float_t>> transform, glm::vec2 center, glm::vec2 dimensions, float_t near, float_t far);

		const glm::vec2 &getCenter() const;
		void setCenter(const glm::vec2 &mCenter);

		const glm::vec2 &getDimensions() const;
		void setDimensions(const glm::vec2 &mDimensions);

	private:
		glm::mat4 calculateMatrix() override;

		glm::vec2 mCenter;
		glm::vec2 mDimensions;
	};
}
