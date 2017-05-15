#pragma once

#include "Light.h"

namespace os
{
    class PointLight : protected Light
    {
        glm::vec3 position;
    public:
        void setPosition(float_t x, float_t y, float_t z);
        void setPostion(glm::vec3 position);
        glm::vec3& getPosition();

        void loadUniforms(Shader* shader);
    };
}