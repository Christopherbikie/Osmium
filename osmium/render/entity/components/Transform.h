#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "BaseComponent.h"
#include "../../graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace os
{
	template <int D, typename T>
	class Transform : public BaseComponent
	{
	public:
		Transform()
		{
			mPosition = glm::vec<D, T>(0);
			mRotation = glm::vec<D, T>(0);
			mScale = glm::vec<D, float>(1);
		}

		void loadMatrices(std::shared_ptr<Shader> shader)
		{
			if (D == 2)
			{
				// Not implemented yet
				assert(false);
			}
			else if (D == 3)
			{
				glm::mat4 model;

				model = glm::translate(model, (glm::vec3) mPosition);
				if (mRotation.x != 0 || mRotation.y != 0 || mRotation.z != 0)
					model *= glm::toMat4(glm::quat(mRotation));
				model = glm::scale(model, (glm::vec3) mScale);

				glm::mat3 normal = glm::inverseTranspose(glm::mat3(model));

				shader->loadUniform("model", model);
				shader->loadUniform("normalMat", normal);
			}
		}

		inline glm::vec<D, T>& getPosition() { return mPosition; }
		inline glm::vec<D, T>& getRotation() { return mRotation; };
		inline glm::vec<D, float_t>& getScale() { return mScale; };

		void setPosition(const glm::highp_dvec3 position) { mPosition = position; }
		void setRotation(const glm::vec<D, T>& rotation) { mRotation = rotation; }
		void setScale(const glm::vec<D, float>& scale) { mScale = scale; }

	private:
		glm::vec<D, T> mPosition;
		glm::vec<D, T> mRotation;
		glm::vec<D, float> mScale;
	};
}
