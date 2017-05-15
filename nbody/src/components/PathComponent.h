#pragma once

#include <render/entity/components/Transform.h>
#include <render/graphics/Shader.h>
#include <render/graphics/VAO.h>
#include <glm/glm.hpp>
#include <imgui.h>

template <uint32_t D, typename T>
class PathComponent : public os::BaseComponent
{
public:
	PathComponent(std::shared_ptr<os::Transform<D, T>> transform) :
			mTransform(transform)
	{
		currBufferSize = nextBufferSize;
		currCoordShowSize = nextCoordShowSize;

		mCoords.resize(currCoordShowSize + currBufferSize, glm::vec<D, T>(0.0f));

		mVAO = std::make_shared<os::VAO>();
		mVAO->storeInBuffer(0, D, (currCoordShowSize + currBufferSize) * D, &mCoords.front().x);
		currIndex = 0;
		mColour = glm::vec3(1.0f);
		mEnabled = true;
	}

	void updatePath()
	{
		mCoords[currIndex++] = (glm::vec<D, float_t>) mTransform->getPosition();

		if (currIndex == currCoordShowSize + currBufferSize)
		{
			memmove(&mCoords[0], &mCoords[currBufferSize], currCoordShowSize * D * sizeof(float_t));
			currIndex = currCoordShowSize;
			memset(&mCoords[currCoordShowSize], 0, currBufferSize * D * sizeof(float_t));
		}

		mVAO->subBuffer(0, (float_t *) mCoords.data(), D, currCoordShowSize + currBufferSize);
	}

	void renderPath(std::shared_ptr<os::Shader> shader)
	{
		if (!mEnabled)
			return;
		shader->loadUniform("pathColour", mColour);
		mVAO->bind();
		shader->drawArrays(0, currCoordShowSize + currBufferSize, GL_LINE_STRIP);
		mVAO->unbind();
	}

	void showUIOptions()
	{
		ImGui::Text("Currently at coordinate %u/%u", currIndex, currCoordShowSize + currBufferSize);

		ImGui::Checkbox("Trails enabled", &mEnabled);
		ImGui::SameLine();
		if (ImGui::Button("Reset trails"))
		{
			memset(&mCoords[0], 0, (currBufferSize + currCoordShowSize) * D * sizeof(float_t));
			currCoordShowSize = nextCoordShowSize;
			currBufferSize = nextBufferSize;
			mCoords.resize(currCoordShowSize + currBufferSize, glm::vec<D, T>(0.0f));
			currIndex = 0;
		}

		ImGui::ColorEdit3("Path colour", (float *) &mColour);

		ImGui::Text("Advanced settings (requires trail reset)");
		ImGui::SliderInt("History size", (int32_t *) &nextCoordShowSize, 0, 0x8000, "%.0f coordinates");
		ImGui::SliderInt("Buffer size", (int32_t *) &nextBufferSize, 1, 0x200, "%.0f coordinates");
	}

private:
	std::shared_ptr<os::Transform<D, T>> mTransform;
	std::shared_ptr<os::VAO> mVAO;

	uint32_t nextBufferSize = 0x80;
	uint32_t nextCoordShowSize = 0x1000 - nextBufferSize;

	std::vector<glm::vec<D, float_t>> mCoords;
	uint32_t currBufferSize = nextBufferSize;
	uint32_t currCoordShowSize = nextCoordShowSize;
	uint32_t currIndex;

	glm::vec3 mColour;
	bool mEnabled;
};