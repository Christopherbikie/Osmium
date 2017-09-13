#pragma once

#include <glm/glm.hpp>
#include <cmath>
#include "BaseComponent.h"
#include "Transform.h"
#include "../../graphics/Shader.h"

namespace os
{
	class Camera : public BaseComponent
	{
	public:
		Camera(std::shared_ptr<Transform<3, float_t>> transform, float_t near, float_t far);

		glm::mat4 getProjMatrix();
		glm::mat4 getViewMatrix();

		void loadMatrices(std::shared_ptr<Shader> shader);
		void loadPosition(std::shared_ptr<Shader> shader);

		float_t getNear() const;
		void setNear(float_t near);

		float_t getFar() const;
		void setFar(float_t far);

	protected:
		virtual glm::mat4 calculateMatrix() = 0;

		void setCacheNeedsRefresh();

		std::shared_ptr<Transform<3, float_t>> mTransform;

		float_t mNear;
		float_t mFar;

	private:
		glm::mat4 matrixCache;
		bool matrixCacheNeedsRefresh;
	};
}
