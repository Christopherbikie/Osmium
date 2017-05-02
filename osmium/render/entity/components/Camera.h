#pragma once

#include <glm/glm.hpp>
#include <cmath>
#include "BaseComponent.h"

namespace os
{
	class Camera : public BaseComponent
	{
	public:
		Camera(float_t near, float_t far);

		glm::mat4 getMatrix();

		float_t getNear() const;
		void setNear(float_t near);

		float_t getFar() const;
		void setFar(float_t far);

	protected:
		virtual glm::mat4 calculateMatrix() = 0;

		void setCacheNeedsRefresh();

		float_t mNear;
		float_t mFar;

	private:
		glm::mat4 matrixCache;
		bool matrixCacheNeedsRefresh;
	};
}
