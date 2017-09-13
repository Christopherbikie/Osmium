#include "GBuffer.h"

namespace os
{

	GBuffer::GBuffer()
	{
		mBuffer = framebufferManager::createFramebuffer();
		mBuffer->addTextureAttachment(true);
		mBuffer->addTextureAttachment(true);
		mBuffer->addTextureAttachment(false);
		mBuffer->addTextureAttachment(false);
		mBuffer->addDepthStencilBuffer();
		mBuffer->checkComplete();
		mBuffer->bindDefault();

		mRectVAO = std::make_shared<VAO>();
		mRectVAO->storeInBuffer(0, 2, 12, quadVertices);
		mRectVAO->storeInBuffer(1, 2, 12, quadTexCoords);
	}

	void GBuffer::bindBuffer()
	{
		mBuffer->bind();
	}

	void GBuffer::runLightPass(std::shared_ptr<Shader> shader)
	{
		mBuffer->getTexture(GBufferTexIndices::position)->bind(shader, "position");
		mBuffer->getTexture(GBufferTexIndices::normal)->bind(shader, "normal");
		mBuffer->getTexture(GBufferTexIndices::albedo)->bind(shader, "albedo");
		mBuffer->getTexture(GBufferTexIndices::specular)->bind(shader, "specular");

		mRectVAO->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void GBuffer::resize(glm::ivec2 dimensions)
	{
		mBuffer->resize(dimensions);
	}

}
