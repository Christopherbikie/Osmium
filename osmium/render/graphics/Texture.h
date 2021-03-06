#pragma once

#include <string>
#include <glad/glad.h>
#include <memory>
#include "Shader.h"

namespace os
{
	class Texture
	{
	public:
		Texture(std::string path);
		Texture(glm::ivec2 dimensions, bool floatingPoint = false);
		~Texture();

		void bind(std::shared_ptr<Shader> shader, std::string uniformName) const;
		void unbind();

		void resize(glm::ivec2 &dimensions);

		GLuint getLocation();
		std::string getPath();
		glm::ivec2 getDimensions();
		int getSizeBytes();

	private:
		GLuint mLocation;
		std::string mPath;
		glm::ivec2 mDimensions;
		bool mFloatingPoint;
	};
}
