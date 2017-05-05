#include "CameraPerspective.h"

namespace os
{
	CameraPerspective::CameraPerspective(std::shared_ptr<Transform<3, float_t>> transform, float_t fov, float_t aspectRatio, float_t near, float_t far) :
		Camera(transform, near, far),
	    mFOV(glm::radians(fov)),
	    mAspectRatio(aspectRatio)
	{ }

	float_t CameraPerspective::getFov() const
	{
		return glm::degrees(mFOV);
	}

	void CameraPerspective::setFov(float_t fov)
	{
		mFOV = glm::radians(fov);
		setCacheNeedsRefresh();
	}

	float_t CameraPerspective::getAspectRatio() const
	{
		return mAspectRatio;
	}

	void CameraPerspective::setAspectRatio(float_t aspectRatio)
	{
		mAspectRatio = aspectRatio;
		setCacheNeedsRefresh();
	}

	glm::mat4 CameraPerspective::calculateMatrix()
	{
		return glm::perspective(mFOV, mAspectRatio, mNear, mFar);
	}
}
