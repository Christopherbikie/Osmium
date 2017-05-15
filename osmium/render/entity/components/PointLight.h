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
        void loadUniforms(Shader* shader); // We're doing it here so we can have it parented to the transform
    };
}


