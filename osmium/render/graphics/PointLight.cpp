#include "PointLight.h"

namespace os
{
    void PointLight::setPosition(float_t x, float_t y, float_t z)
    {
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
    }

    void PointLight::setPosition(glm::vec3 position)
    {
        this->position = position;
    }

    glm::vec3& PointLight::getPosition()
    {
        return this->position;
    }

    void PointLight::loadUniforms(Shader* shader)
    {
        shader->loadUniform("light.position", this->position);
        shader->loadUniform("light.color", this->color);
        shader->loadUniform("light.intensity", this->intensity);
    }
}