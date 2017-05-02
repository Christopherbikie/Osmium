#include "Camera.h"

namespace os
{
	Camera::Camera(float_t near, float_t far) :
		matrixCacheNeedsRefresh(true),
		mNear(near),
	    mFar(far)
	{ }

	glm::mat4 Camera::getMatrix()
	{
		if (matrixCacheNeedsRefresh)
		{
			matrixCache = calculateMatrix();
			matrixCacheNeedsRefresh = false;
		}
		return matrixCache;
	}

	float_t Camera::getNear() const
	{
		return mNear;
	}

	void Camera::setNear(float_t near)
	{
		Camera::mNear = near;
		setCacheNeedsRefresh();
	}

	float_t Camera::getFar() const
	{
		return mFar;
	}

	void Camera::setFar(float_t far)
	{
		Camera::mFar = far;
		setCacheNeedsRefresh();
	}

	void Camera::setCacheNeedsRefresh()
	{
		matrixCacheNeedsRefresh = true;
	}
}
