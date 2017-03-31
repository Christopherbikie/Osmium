#pragma once

#include <vector>
#include <map>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <cctype>

namespace os
{
	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	};

	class ShaderSource
	{
	public:
		ShaderSource(ShaderType type, std::string path);

		const ShaderType type;
		const std::string path;

		bool operator==(const ShaderSource &other) const;
	};

	extern const std::map<GLuint, std::string> shaderTypeNames;

	class Shader
	{
	public:
		Shader();
		~Shader();

		void addSource(ShaderType type, const GLchar *path);
		void link();
		void use() const;

		void reload();

		void loadUniform(std::string name, bool value) const;
		void loadUniform(std::string name, int32_t value) const;
		void loadUniform(std::string name, float_t value) const;
		void loadUniform(std::string name, double_t value) const;
		void loadUniform(std::string name, glm::vec2 vector) const;
		void loadUniform(std::string name, glm::vec3 vector) const;
		void loadUniform(std::string name, glm::vec4 vector) const;
		void loadUniform(std::string name, glm::mat4 matrix) const;

		void drawArrays(int32_t first, int32_t count, GLenum primitiveType = GL_TRIANGLES) const;
		void drawElements(int32_t count, GLenum primitiveType = GL_TRIANGLES) const;

		GLuint getLocation() const;

		GLint getAttribLocation(std::string attribName) const;

	private:
		GLuint mProgram;
		std::vector<GLuint> mShaders;
		std::vector<ShaderSource> mSources;
		bool mLinked = false;
	};

	void reloadShaders();
}
