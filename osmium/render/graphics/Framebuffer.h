#pragma once

#include <cstdint>
#include <memory>
#include "Texture.h"
#include "../../app/Settings.h"

namespace os
{
	class Framebuffer
	{
	public:
		Framebuffer();
		Framebuffer(glm::ivec2 dimensions);
		~Framebuffer();

		void bind();
		static void bindDefault();

		size_t addTextureAttachment(glm::ivec2 dimensions = settings::getViewport());
		void addDepthStencilBuffer(glm::ivec2 dimensions = settings::getViewport());

		int checkComplete();

		void setClearColour(glm::vec3 clearColour);
		void clear(GLenum clearBits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::shared_ptr<Texture> getTexture(size_t index);

		uint32_t getLocation() const;

	private:
		uint32_t mLocation;
		std::vector<std::shared_ptr<Texture>> mTextures;
		uint32_t mRBO;

		glm::vec3 mClearColour;
	};
}
