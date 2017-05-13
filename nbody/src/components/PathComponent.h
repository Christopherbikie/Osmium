#pragma once

#include <render/entity/components/Transform.h>
#include <render/graphics/Shader.h>
#include <glm/glm.hpp>

template <uint32_t D, typename T>
class PathComponent : public os::BaseComponent
{
	static const uint32_t bufferSize = 0x80;
	static const uint32_t coordShowSize = 0x1000 - bufferSize;

public:
	PathComponent(std::shared_ptr<os::Transform<D, T>> transform) :
			mTransform(transform)
	{
		mCoords.resize(coordShowSize + bufferSize, glm::vec3(0.0f));

		mVAO = std::make_shared<os::VAO>();
		mVAO->storeInBuffer(0, D, (coordShowSize + bufferSize) * D, &mCoords.front().x);
		currIndex = 0;
	}

	void updatePath()
	{
		mCoords[currIndex++] = (glm::vec<D, float_t>) mTransform->getPosition();

		if (currIndex == coordShowSize + bufferSize)
		{
			memmove(&mCoords[0], &mCoords[bufferSize], coordShowSize * D * sizeof(float_t));
			currIndex = coordShowSize;
			memset(&mCoords[coordShowSize], 0, bufferSize * D * sizeof(float_t));
		}

		mVAO->subBuffer(0, (float_t *) mCoords.data(), D, coordShowSize + bufferSize);
	}

	void renderPath(std::shared_ptr<os::Shader> shader)
	{
		mVAO->bind();
		shader->drawArrays(0, coordShowSize + bufferSize, GL_LINE_STRIP);
		mVAO->unbind();
	}

private:
	std::shared_ptr<os::Transform<D, T>> mTransform;
	std::vector<glm::vec<D, float_t>> mCoords;
	std::shared_ptr<os::VAO> mVAO;
	uint32_t currIndex;
};
