#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Camera.h"

namespace os
{
	Camera::Camera(std::shared_ptr<Transform<3, float_t>> transform, float_t near, float_t far) :
		matrixCacheNeedsRefresh(true),
		mTransform(transform),
		mNear(near),
	    mFar(far)
	{ }

	glm::mat4 Camera::getProjMatrix()
	{
		if (matrixCacheNeedsRefresh)
		{
			matrixCache = calculateMatrix();
			matrixCacheNeedsRefresh = false;
		}
		return matrixCache;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		glm::mat4 trans;

		glm::vec3 rotation = mTransform->getRotation();
		if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0)
		{
			trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		trans = glm::translate(trans, -((glm::vec3) mTransform->getPosition()));

		return trans;
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
