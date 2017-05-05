#include "CameraOrthographic.h"

namespace os
{
	CameraOrthographic::CameraOrthographic(std::shared_ptr<Transform<3, float_t>> transform, glm::vec2 center, glm::vec2 dimensions, float_t near, float_t far) :
		Camera(transform, near, far),
	    mCenter(center),
	    mDimensions(dimensions)
	{ }

	const glm::vec2 &CameraOrthographic::getCenter() const
	{
		return mCenter;
	}

	void CameraOrthographic::setCenter(const glm::vec2 &mCenter)
	{
		CameraOrthographic::mCenter = mCenter;
		setCacheNeedsRefresh();
	}

	const glm::vec2 &CameraOrthographic::getDimensions() const
	{
		return mDimensions;
	}

	void CameraOrthographic::setDimensions(const glm::vec2 &mDimensions)
	{
		CameraOrthographic::mDimensions = mDimensions;
		setCacheNeedsRefresh();
	}

	glm::mat4 CameraOrthographic::calculateMatrix()
	{
		float_t left = mCenter.x - mDimensions.x / 2;
		float_t right = mCenter.x + mDimensions.x / 2;
		float_t top = mCenter.y + - mDimensions.y / 2;
		float_t bottom = mCenter.y + mDimensions.y / 2;

		return glm::ortho(left, right, bottom, top, mNear, mFar);
	}


}
