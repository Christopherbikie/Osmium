#include <iostream>
#include "Framebuffer.h"

namespace os
{

	Framebuffer::Framebuffer() : Framebuffer(settings::getViewport())
	{ }

	Framebuffer::Framebuffer(glm::ivec2 dimensions)
	{
		glGenFramebuffers(1, &mLocation);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &mLocation);
		if (mRBO)
			glDeleteRenderbuffers(1, &mRBO);
	}

	void Framebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mLocation);
	}

	void Framebuffer::bindDefault()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	size_t Framebuffer::addTextureAttachment(glm::ivec2 dimensions)
	{
		GLint maxAttachments;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);
		if (mTextures.size() >= maxAttachments)
		{
			std::cout << "Attempted to add to many color attachments to framebuffer (max " << maxAttachments << ")" << std::endl;
			return (size_t) 0;
		}

		bind();
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(dimensions);
		texture->unbind();
		size_t index = mTextures.size();
		mTextures.push_back(texture);
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum) (GL_COLOR_ATTACHMENT0 + index), GL_TEXTURE_2D, texture->getLocation(), 0);
		return index;
	}

	void Framebuffer::addDepthStencilBuffer(glm::ivec2 dimensions)
	{
		bind();
		glGenRenderbuffers(1, &mRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, dimensions.x, dimensions.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);
	}

	int Framebuffer::checkComplete()
	{
		bind();
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "Failed to complete framebuffer! Status: " << std::hex << status << std::endl;
			return status;
		}
		return 0;
	}

	void Framebuffer::setClearColour(glm::vec3 clearColour)
	{
		mClearColour = clearColour;
	}

	void Framebuffer::clear(GLenum clearBits)
	{
		bind();
		glClearColor(mClearColour.r, mClearColour.b, mClearColour.b, 1.0f);
		glClear(clearBits);
	}

	std::shared_ptr<Texture> Framebuffer::getTexture(size_t index)
	{
		if (index < 0 || index >= mTextures.size())
			std::cout << "Framebuffer texture index out of bounds (" << index << " not in range [0," << mTextures.size() << "])" << std::endl;
		return mTextures[index];
	}

	uint32_t Framebuffer::getLocation() const
	{
		return mLocation;
	}
}
