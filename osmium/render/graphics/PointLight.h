#pragma once

#include "Light.h"

namespace os
{
    class PointLight : public Light
    {
        glm::vec3 position;
		float_t constant;
		float_t linear;
		float_t quadratic;
    public:
		PointLight();

        void setPosition(float_t x, float_t y, float_t z);
        void setPosition(glm::vec3 position);
        glm::vec3& getPosition();

		void setConstant(float_t newConstant);
		float_t getConstant();

		void setLinear(float_t newLinear);
		float_t getLinear();

		void setQuadratic(float_t newQuadratic);
		float_t getQuadratic();

        void loadUniforms(Shader* shader);
    };
}