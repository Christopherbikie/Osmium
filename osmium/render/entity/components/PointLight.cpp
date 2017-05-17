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

	void PointLightComponent::setColor(float_t r, float_t g, float_t b)
    {
		this->light->setColor(r, g, b);
    }
	const glm::vec3& PointLightComponent::getColor()
    {
		return this->light->getColor();
    }

	void PointLightComponent::setIntensity(float_t intensity)
    {
		this->light->setIntensity(intensity);
    }

	float_t PointLightComponent::getIntensity()
    {
		return this->light->getIntensity();
    }

    void PointLightComponent::loadUniforms(Shader* shader) {
        std::shared_ptr<Transform<3, float_t>> transformComponent = std::static_pointer_cast<Transform<3, float_t>>(this->getParent()->getComponent("Transform"));

    	glm::vec3 pos;
		pos.x = static_cast<float_t>(transformComponent->getPosition().x);
		pos.y = static_cast<float_t>(transformComponent->getPosition().y);
		pos.z = static_cast<float_t>(transformComponent->getPosition().z);

    	shader->loadUniform("light.position", pos); // FIXME: This is a really bad way of doing it
        shader->loadUniform("light.color", this->light->getColor());
        shader->loadUniform("light.intensity", this->light->getIntensity());
    }
}