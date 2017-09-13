#pragma once

#include "Framebuffer.h"
#include "VAO.h"

namespace os
{
	static float quadVertices[] = {
			-1.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, -1.0f,
			-1.0f, 1.0f,
			1.0f, -1.0f,
			1.0f, 1.0f,
	};

	static float quadTexCoords[] = {
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
	};

	enum GBufferTexIndices
	{
		position,
		normal,
		albedo,
		specular,
	};

	class GBuffer
	{
	public:
		GBuffer();

		void bindBuffer();
		void runLightPass(std::shared_ptr<Shader>);

		void resize(glm::ivec2 dimensions);

	private:
		std::shared_ptr<Framebuffer> mBuffer;
		std::shared_ptr<VAO> mRectVAO;
	};
}
