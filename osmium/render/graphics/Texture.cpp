#include "Texture.h"
#include <SOIL.h>

namespace os
{
	Texture::Texture(std::string path)
		: mPath(path)
	{
		glGenTextures(1, &mLocation);
		unsigned char *image = SOIL_load_image(mPath.c_str(), &mDimensions.x, &mDimensions.y, 0, SOIL_LOAD_RGB);

		glBindTexture(GL_TEXTURE_2D, mLocation);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mDimensions.x, mDimensions.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		SOIL_free_image_data(image);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mLocation);
	}

	void Texture::bind(Shader *shader, std::string uniformName) const
	{
		GLint location = glGetUniformLocation(shader->getLocation(), uniformName.c_str());
		glActiveTexture((GLenum) (GL_TEXTURE0 + location));
		glBindTexture(GL_TEXTURE_2D, mLocation);
		glUniform1i(location, location);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::getLocation()
	{
		return mLocation;
	}

	std::string Texture::getPath()
	{
		return mPath;
	}

	glm::ivec2 Texture::getDimensions()
	{
		return mDimensions;
	}

	int Texture::getSizeBytes()
	{
		return mDimensions.x * mDimensions.y * 3;
	}
}
