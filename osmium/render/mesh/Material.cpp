#include "Material.h"
#include "../../assets/TextureStore.h"

#include <GLFW/glfw3.h>

namespace os
{
	Material::Material()
	{
	}

	// Albedo Map
	void Material::setDiffuseMap(std::string diffuse)
	{
		diffuseMap = textureStore::get(diffuse);
	}

	std::shared_ptr<Texture> Material::getDiffuseMap()
	{
		return this->diffuseMap;
	}

	// Normal Map
	void Material::setAmbientMap(std::string ambient)
	{
		ambientMap = textureStore::get(ambient);
	}
	std::shared_ptr<Texture> Material::getAmbientMap()
	{
		return this->ambientMap;
	}
	

	// Specular Map
	void Material::setSpecularMap(std::string specular)
	{
		specularMap = textureStore::get(specular);
	}
	std::shared_ptr<Texture> Material::getSpecularMap()
	{
		return this->specularMap;
	}

	// Height Map
	void Material::setSpecularHighlightsMap(std::string highlights)
	{
		specularHighlightsMap = textureStore::get(highlights);
	}
	std::shared_ptr<Texture> Material::getSpecularHighlightsMap()
	{
		return this->specularHighlightsMap;
	}

	// Load Uniforms
	void Material::bind(std::shared_ptr<Shader> shader)
	{
		int32_t loadFlags = 0;

		if (diffuseMap)
		{
			loadFlags = loadFlags | DIFFUSE_BIT;
			diffuseMap->bind(shader, "material.diffuse_map");
		} else
			shader->loadUniform("material.diffuse", albedo);

		if (ambientMap)
		{
			loadFlags = loadFlags | AMBIENT_BIT;
			ambientMap->bind(shader, "material.ambient_map");
		} else
			shader->loadUniform("material.ambient", albedo);

		if (specularMap)
		{
			loadFlags = loadFlags | SPECULAR_BIT;
			specularMap->bind(shader, "material.specular_map");
		} else
			shader->loadUniform("material.specular", specular);

		if (specularHighlightsMap)
		{
			loadFlags = loadFlags | SPECULAR_HIGHLIGHT_BIT;
			specularHighlightsMap->bind(shader, "material.highlight_map");
		} else
			shader->loadUniform("material.highlight", specular);

		shader->loadUniform("material.shader_parameters", loadFlags);
	}

	void Material::unbind()
	{
		if (diffuseMap)
		{
			diffuseMap->unbind();
		}

		if (ambientMap)
		{
			ambientMap->unbind();
		}

		if (specularMap)
		{
			specularMap->unbind();
		}

		if (specularHighlightsMap)
		{
			specularHighlightsMap->unbind();
		}
	}
}
