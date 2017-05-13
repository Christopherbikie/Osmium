#include "Material.h"

#include <GLFW/glfw3.h>

namespace os
{
	Material::Material()
	{
	}

	Material::Material(std::string diffuse, std::string ambient, std::string specular, std::string height, std::string emission)
	{
		if (diffuse != "")
		{
			diffuseMap = std::make_shared<Texture>(Texture(diffuse));
		}

		if (ambient != "")
		{
			ambientMap = std::make_shared<Texture>(Texture(ambient));
		}

		if (specular != "")
		{
			specularMap = std::make_shared<Texture>(Texture(specular));
		}

		if (height != "")
		{
			specularHighlightsMap = std::make_shared<Texture>(Texture(height));
		}

		if (emission != "")
		{
			emissionMap = std::make_shared<Texture>(Texture(emission));
		}
	}

	Material::Material(Texture albedo, Texture normal, Texture specular, Texture height, Texture emission)
	{
		diffuseMap = std::make_shared<Texture>(albedo);
		ambientMap = std::make_shared<Texture>(normal);
		specularMap = std::make_shared<Texture>(specular);
		specularHighlightsMap = std::make_shared<Texture>(height);
		emissionMap = std::make_shared<Texture>(emission);
	}

	// Albedo Map
	void Material::setDiffuseMap(std::string diffuse)
	{
		Texture *newTex = new Texture(diffuse);
		diffuseMap = std::shared_ptr<Texture>(newTex);
	}
	void Material::setDiffuseMap(Texture diffuse)
	{
		diffuseMap = std::make_shared<Texture>(diffuse);
	}
	std::shared_ptr<Texture> Material::getDiffuseMap()
	{
		return this->diffuseMap;
	}

	// Normal Map
	void Material::setAmbientMap(std::string normal)
	{
		ambientMap = std::make_shared<Texture>(Texture(normal));
	}
	void Material::setAmbientMap(Texture normal)
	{
		ambientMap = std::make_shared<Texture>(normal);
	}
	std::shared_ptr<Texture> Material::getAmbientMap()
	{
		return this->ambientMap;
	}
	

	// Specular Map
	void Material::setSpecularMap(std::string specular)
	{
		specularMap = std::make_shared<Texture>(Texture(specular));
	}
	void Material::setSpecularMap(Texture specular)
	{
		specularMap = std::make_shared<Texture>(specular);
	}
	std::shared_ptr<Texture> Material::getSpecularMap()
	{
		return this->specularMap;
	}

	// Height Map
	void Material::setSpecularHighlightsMap(std::string highlights)
	{
		specularHighlightsMap = std::make_shared<Texture>(Texture(highlights));
	}
	void Material::setSpecularHighlightsMap(Texture highlights)
	{
		specularHighlightsMap = std::make_shared<Texture>(highlights);
	}
	std::shared_ptr<Texture> Material::getSpecularHighlightsMap()
	{
		return this->specularHighlightsMap;
	}

	// Emission Map
	void Material::setEmissionMap(std::string emission)
	{
		emissionMap = std::make_shared<Texture>(Texture(emission));
	}
	void Material::setEmissionMap(Texture emission)
	{
		emissionMap = std::make_shared<Texture>(emission);
	}
	std::shared_ptr<Texture> Material::getEmissionMap()
	{
		return this->emissionMap;
	}

	// Load Uniforms
	void Material::bind(Shader* shader)
	{
		int32_t loadFlags = 0;

		if (diffuseMap)
		{
			diffuseMap->bind(shader, "diffuse");
		}

		/*
		if (ambientMap)
		{
			loadFlags = loadFlags | (1 << 1);
			glActiveTexture(GL_TEXTURE1);
			ambientMap->bind(shader, "material.ambient_map");
		}

		if (specularMap)
		{
			loadFlags = loadFlags | (1 << 2);
			glActiveTexture(GL_TEXTURE2);
			specularMap->bind(shader, "material.specular_map");
		}

		if (specularHighlightsMap)
		{
			loadFlags = loadFlags | (1 << 3);
			glActiveTexture(GL_TEXTURE3);
			specularHighlightsMap->bind(shader, "material.highlights_map");
		}

		shader->loadUniform("material.shader_paremeters", loadFlags);
		*/
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
