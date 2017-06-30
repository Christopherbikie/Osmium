#include "PointLight.h"

namespace os
{
	PointLight::PointLight()
	{
		this->setConstant(1.0);
		this->setLinear(0.07);
		this->setQuadratic(0.017);
		this->setIntensity(1.0);
	}

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

	void PointLight::setConstant(float_t newConstant)
	{
		this->constant = newConstant;
	}
	float_t PointLight::getConstant()
	{
		return this->constant;
	}

	void PointLight::setLinear(float_t newLinear)
	{
		this->linear = newLinear;
	}

	float_t PointLight::getLinear()
	{
		return this->linear;
	}

	void PointLight::setQuadratic(float_t newQuadratic)
	{
		this->quadratic = newQuadratic;
	}

	float_t PointLight::getQuadratic()
	{
		return this->quadratic;
	}


    void PointLight::loadUniforms(Shader* shader)
    {
        shader->loadUniform("light.position", this->position);
        shader->loadUniform("light.color", this->color);
        shader->loadUniform("light.intensity", this->intensity);
		shader->loadUniform("light.constant", this->getConstant());
		shader->loadUniform("light.linear", this->getLinear());
		shader->loadUniform("light.quadratic", this->getQuadratic());
    }
}