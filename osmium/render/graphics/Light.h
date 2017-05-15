#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

namespace os
{
    class Light
    {
    protected:
        glm::vec3 color;
        float_t intensity;
    public:
        void setColor(float_t r, float_t g, float_t b);

        void setColor(glm::vec3);

        const glm::vec3 &getColor();

        virtual void loadUniforms(Shader* shader) = 0;
    };
}