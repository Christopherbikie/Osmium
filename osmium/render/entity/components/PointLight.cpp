#include "PointLight.h"

namespace os
{
    PointLightComponent::PointLightComponent()
    {
        this->light = std::shared_ptr<PointLight>(new PointLight());
    }
}


