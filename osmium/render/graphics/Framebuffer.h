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
		Framebuffer(bool clearOnRefresh = true);
		~Framebuffer();

		void bind();
		static void bindDefault();

		size_t addTextureAttachment(glm::ivec2 dimensions = settings::getViewport());
		void addDepthStencilBuffer(glm::ivec2 dimensions = settings::getViewport());

		int checkComplete();

		void setClearOnRefresh(bool value);
		void refresh();

		void resize(glm::ivec2 &dimensions);

		void setClearColour(glm::vec3 clearColour);
		void clear(GLenum clearBits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::shared_ptr<Texture> getTexture(size_t index);

		std::vector<std::shared_ptr<Texture>> &getTextures();

		uint32_t getLocation() const;

	private:
		uint32_t mLocation;
		std::vector<std::shared_ptr<Texture>> mTextures;
		uint32_t mRBO;

		bool mClearOnRefresh;
		glm::vec3 mClearColour;
	};

	namespace framebufferManager
	{
		std::shared_ptr<Framebuffer> createFramebuffer(bool clearOnRefresh = true);

		void clearBuffers();

		void showDebugWindow();

	}
}
