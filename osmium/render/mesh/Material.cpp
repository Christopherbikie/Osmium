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
			loadFlags = loadFlags | (1 << 0);
			diffuseMap->bind(shader, "Material.diffuse_map");
		}

		if (ambientMap)
		{
			loadFlags = loadFlags | (1 << 1);
			ambientMap->bind(shader, "Material.ambient_map");
		}

		if (specularMap)
		{
			loadFlags = loadFlags | (1 << 2);
			specularMap->bind(shader, "Material.specular_map");
		}

		if (specularHighlightsMap)
		{
			loadFlags = loadFlags | (1 << 3);
			specularHighlightsMap->bind(shader, "Material.highlight_map");
		}

		shader->loadUniform("Material.shader_parameters", loadFlags);
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
