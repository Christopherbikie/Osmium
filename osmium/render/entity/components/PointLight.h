#pragma once

#include "BaseComponent.h"
#include "../../graphics/PointLight.h"

#include <memory>


namespace os
{
    class PointLightComponent : public BaseComponent
    {
        std::shared_ptr<PointLight> light;
    public:
        PointLightComponent();

		void setColor(float_t r, float_t g, float_t b);
		const glm::vec3& getColor();

		void setIntensity(float_t intensity);
		float_t getIntensity();


        void loadUniforms(Shader* shader); // We're doing it here so we can have it parented to the transform
    };
}


