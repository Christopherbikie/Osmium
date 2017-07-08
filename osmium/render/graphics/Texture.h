#pragma once

#include <string>
#include <glad/glad.h>
#include "Shader.h"

namespace os
{
	class Texture
	{
	public:
		Texture(std::string path);
		~Texture();

		void bind(Shader *shader, std::string uniformName) const;
		void unbind();

		GLuint getLocation();
		std::string getPath();
		glm::ivec2 getDimensions();
		int getSizeBytes();

	private:
		GLuint mLocation;
		std::string mPath;
		glm::ivec2 mDimensions;
	};
}
