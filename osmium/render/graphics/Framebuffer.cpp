#include <iostream>
#include <imgui.h>
#include "Framebuffer.h"

namespace os
{
	Framebuffer::Framebuffer(bool clearOnRefresh)
			: mClearOnRefresh(clearOnRefresh)
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

	void Framebuffer::setClearOnRefresh(bool value)
	{
		mClearOnRefresh = value;
	}

	void Framebuffer::refresh()
	{
		if (mClearOnRefresh)
			clear();
	}

	void Framebuffer::resize(glm::ivec2 &dimensions)
	{
		for (auto texture : mTextures)
			texture->resize(dimensions);
		if (mRBO)
		{
			glDeleteRenderbuffers(1, &mRBO);
			this->addDepthStencilBuffer(dimensions);
		}
		checkComplete();
		bindDefault();
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

	std::vector<std::shared_ptr<Texture>> &Framebuffer::getTextures()
	{
		return mTextures;
	}

	namespace framebufferManager
	{
		std::vector<std::weak_ptr<Framebuffer>> framebuffers;

		std::shared_ptr<Framebuffer> createFramebuffer(bool clearOnRefresh)
		{
			auto framebuffer = std::make_shared<Framebuffer>(clearOnRefresh);
			std::weak_ptr<Framebuffer> wptr = framebuffer;
			framebuffers.push_back(wptr);
			return framebuffer;
		}

		void clearBuffers()
		{
			for (auto it = framebuffers.begin(); it < framebuffers.end(); it++)
			{
				if ((*it).expired())
					framebuffers.erase(it);
				else
					(*it).lock()->refresh();
			}
		}

		void showDebugWindow()
		{
			// Size is about right to view a framebuffer with 4 textures without scrolling or resizing
			ImGui::SetNextWindowSize(ImVec2(800, 475), ImGuiSetCond_Once);
			ImGui::Begin("Framebuffers");

			float width = -1;

			for (auto it = framebuffers.begin(); it < framebuffers.end(); it++)
			{
				int index = (int) (it - framebuffers.begin());
				char bufferName[5];
				sprintf(bufferName, "[%d]", index);
				if (ImGui::TreeNodeEx(bufferName, ImGuiTreeNodeFlags_DefaultOpen))
				{
					if ((*it).expired())
						framebuffers.erase(it);
					else
					{
						bool nextOnNewLine = true;
						for (auto texture : (*it).lock()->getTextures())
						{
							glm::vec2 size = texture->getDimensions();
							if (width == -1)
								width = ImGui::GetContentRegionAvailWidth() / 2 - ImGui::GetStyle().ItemSpacing.x;
							float scale = width / size.x;
							size *= scale;

							ImGui::Image((void *) texture->getLocation(), ImVec2(size.x, size.y), ImVec2(0, 1),
							             ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
							if (nextOnNewLine)
								ImGui::SameLine();
							nextOnNewLine = !nextOnNewLine;
						}
					}
					ImGui::TreePop();
				}
			}

			ImGui::End();
		}
	}
}
