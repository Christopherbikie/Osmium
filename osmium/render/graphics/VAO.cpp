#include "VAO.h"
#include <glad/glad.h>

namespace os
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &mLocation);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &mLocation);
	}

	void VAO::bind() const
	{
		glBindVertexArray(mLocation);
	}

	void VAO::unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::storeInBuffer(uint32_t location, uint32_t componentsPerVertex, uint32_t dataSize, float_t *data)
	{
		bind();

		glGenBuffers(1, &mVBOs[location]);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOs[location]);
		glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(float_t), data, GL_STATIC_DRAW);

		glVertexAttribPointer(location, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(float_t), nullptr);
		glEnableVertexAttribArray(location);

		unbind();

		if (dataSize > mVertexCount)
			mVertexCount = dataSize;
	}

	void VAO::storeInElementBuffer(uint32_t vertexCount, uint32_t *data)
	{
		bind();

		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(uint32_t), data, GL_STATIC_DRAW);

		unbind();

		if (vertexCount > mVertexCount)
			mVertexCount = vertexCount;
	}

	void VAO::subBuffer(uint32_t location, float_t *data, uint32_t componentsPerVertex, uint32_t vertexCount, uint32_t offset)
	{
		bind();
		glBindBuffer(GL_ARRAY_BUFFER, mVBOs[location]);
		glBufferSubData(GL_ARRAY_BUFFER, offset, vertexCount * componentsPerVertex * sizeof(float_t), data);
		unbind();
	}

	void VAO::bindEBO() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	}

	uint32_t VAO::getVertexCount() const
	{
		return mVertexCount;
	}
}
