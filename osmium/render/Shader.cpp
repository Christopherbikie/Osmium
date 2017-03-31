#include "Shader.h"
#include "../util/Loader.h"
#include <iostream>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

namespace os
{
	const std::map<GLuint, std::string> shaderTypeNames{
		{GL_VERTEX_SHADER,          "vertex"},
		{GL_TESS_CONTROL_SHADER,    "tessellation control"},
		{GL_TESS_EVALUATION_SHADER, "tessellation evaluation"},
		{GL_GEOMETRY_SHADER,        "geometry"},
		{GL_FRAGMENT_SHADER,        "fragment"},
	};

	ShaderSource::ShaderSource(ShaderType type, std::string path)
		: type(type), path(path)
	{
	}

	bool ShaderSource::operator==(const ShaderSource &other) const
	{
		return path == other.path;
	}

	std::vector<Shader *> linkedShaders;

	Shader::Shader()
	{
		mProgram = glCreateProgram();
	}

	Shader::~Shader()
	{
		glDeleteProgram(mProgram);
		for (int32_t i = 0; i < linkedShaders.size(); ++i)
		{
			std::vector<Shader *>::iterator iterator = find(linkedShaders.begin(), linkedShaders.end(), this);
			if (iterator != linkedShaders.end())
			{
				linkedShaders.erase(iterator);
				break;
			}
		}
	}

	void Shader::addSource(ShaderType type, const GLchar *path)
	{
		if (mLinked)
		{
			std::cout << "Could not add source located at " << path << " to program, program is already linked!" << std::endl;
			return;
		}

		ShaderSource source = ShaderSource(type, path);
		if (!(std::find(mSources.begin(), mSources.end(), source) != mSources.end()))
			mSources.push_back(source);

		std::string shaderSourceStdString = loadFileAsString(path);
		const GLchar *shaderSource = shaderSourceStdString.c_str();

		GLuint shaderLocation = glCreateShader(type);
		glShaderSource(shaderLocation, 1, &shaderSource, NULL);
		glCompileShader(shaderLocation);

		GLchar infolog[512];
		int32_t success;
		glGetShaderiv(shaderLocation, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderLocation, 512, NULL, infolog);
			std::cout << "Failed to compile " << shaderTypeNames.at(static_cast<GLuint>(type)) << " shader at \""
			          << path << "\"\n" << infolog << std::endl;
		}

		glAttachShader(mProgram, shaderLocation);
		mShaders.push_back(shaderLocation);
	}

	void Shader::link()
	{
		if (mLinked)
		{
			std::cout << "Could not link program, program is already linked!" << std::endl;
			return;
		}

		glLinkProgram(mProgram);

		GLchar infolog[512];
		int32_t success;
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(mProgram, 512, NULL, infolog);
			std::cout << "Failed to link program\n" << infolog << std::endl;
		}

		for (GLuint shader : mShaders)
		{
			glDetachShader(mProgram, shader);
			glDeleteShader(shader);
		}

		mLinked = true;

		linkedShaders.push_back(this);
	}

	void Shader::use() const
	{
		glUseProgram(mProgram);
	}

	void Shader::reload()
	{
		glDeleteProgram(mProgram);
		for (int32_t i = 0; i < linkedShaders.size(); ++i)
		{
			std::vector<Shader *>::iterator iterator = find(linkedShaders.begin(), linkedShaders.end(), this);
			if (iterator != linkedShaders.end())
			{
				linkedShaders.erase(iterator);
				break;
			}
		}

		mProgram = glCreateProgram();
		mLinked = false;

		for (ShaderSource source : mSources)
			this->addSource(source.type, source.path.c_str());

		this->link();
	}

	void Shader::loadUniform(std::string name, bool value) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform1i(uniformLocation, value ? 1 : 0);
	}

	void Shader::loadUniform(std::string name, int32_t value) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform1i(uniformLocation, value);
	}

	void Shader::loadUniform(std::string name, float_t value) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform1f(uniformLocation, value);
	}

	void Shader::loadUniform(std::string name, double_t value) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform1d(uniformLocation, value);
	}

	void Shader::loadUniform(std::string name, glm::vec2 vector) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform2f(uniformLocation, vector.x, vector.y);
	}

	void Shader::loadUniform(std::string name, glm::vec3 vector) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform3f(uniformLocation, vector.x, vector.y, vector.z);
	}

	void Shader::loadUniform(std::string name, glm::vec4 vector) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::loadUniform(std::string name, glm::mat4 matrix) const
	{
		GLint uniformLocation = glGetUniformLocation(mProgram, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint Shader::getLocation() const
	{
		return mProgram;
	}

	GLint Shader::getAttribLocation(std::string attribName) const
	{
		return glGetAttribLocation(mProgram, attribName.c_str());
	}

	void reloadShaders()
	{
		for (int32_t i = 0; i < linkedShaders.size(); ++i)
			linkedShaders[i]->reload();
	}
}
