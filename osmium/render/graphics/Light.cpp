#include "Light.h"

namespace os
{
    void Light::setColor(float_t r, float_t g, float_t b)
    {
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
    }

    void Light::setColor(glm::vec3 color)
    {
        this->color = color;
    }

    const glm::vec3& Light::getColor()
    {
        return this->color;
    }
}