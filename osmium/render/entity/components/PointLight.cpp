#include "PointLight.h"
#include "../LogicalEntity.h"
#include "Transform.h"
#include <memory>

namespace os
{
    PointLightComponent::PointLightComponent()
    {
        this->light = std::shared_ptr<PointLight>(new PointLight());
    }


    void PointLightComponent::loadUniforms(Shader* shader) {
        std::shared_ptr<Transform<3, double_t>> transformComponent = std::static_pointer_cast<Transform<3, double_t>>(this->getParent()->getComponent("Transform"));
        shader->loadUniform("light.position", static_cast<glm::vec3>(transformComponent->getPosition())); // FIXME: This is a really bad way of doing it
        shader->loadUniform("light.color", this->light->getColor());
        shader->loadUniform("light.intensity", this->light->getIntensity());

    }
}


