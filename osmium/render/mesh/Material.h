#pragma once
#include <cmath>
#include <string>
#include "../graphics/Texture.h"
#include "../graphics/Shader.h"
#include <array>
#include <memory>

#define DIFFUSE_BIT (1 << 0)
#define AMBIENT_BIT (1 << 1)
#define SPECULAR_BIT (1 << 2)
#define SPECULAR_HIGHLIGHT_BIT (1 << 3)


namespace os
{
	class Material
	{
	private:
		glm::vec4 albedo;
		glm::vec3 specular;
		glm::vec3 transmittance;
		glm::vec3 emission;
		float_t roughness;
		float_t ior;
		float_t transparency;
	
		bool hasTransparency = false;

		std::shared_ptr<Texture> diffuseMap;
		std::shared_ptr<Texture> ambientMap;
		std::shared_ptr<Texture> specularMap;
		std::shared_ptr<Texture> specularHighlightsMap;
		std::shared_ptr<Texture> emissionMap;
	public:
		Material();

		void setDiffuseMap(std::string diffuse);
		std::shared_ptr<Texture> getDiffuseMap();

		void setAmbientMap(std::string ambient);
		std::shared_ptr<Texture> getAmbientMap();

		void setSpecularMap(std::string specular);
		std::shared_ptr<Texture> getSpecularMap();
		
		void setSpecularHighlightsMap(std::string highlights);
		std::shared_ptr<Texture> getSpecularHighlightsMap();

		void bind(std::shared_ptr<Shader> shader);
		void unbind();

		inline void setAlbedo(glm::vec4 &albedo)
		{
			Material::albedo = albedo;
		}

		inline void setAlbedo(glm::vec3 &albedo)
		{
			Material::albedo = glm::vec4(albedo, 1.0f);
		}

		inline const glm::vec4& getAlbedo() const
		{
			return this->albedo;
		}

		inline void setSpecular(glm::vec3 &specular)
		{
			Material::specular = specular;
		}
		
		inline const glm::vec3& getSpecular() const
		{
			return this->specular;
		}

		inline void setTransmittance(glm::vec3 &transmittance)
		{
			Material::transmittance = transmittance;
		}

		inline const glm::vec3& getTransmittance() const
		{
			return this->transmittance;
		}

		inline void setEmission(glm::vec3 &emission)
		{
			Material::emission = emission;
		}

		inline const glm::vec3& getEmission() const
		{
			return this->emission;
		}

		inline void setRoughness(float_t roughness)
		{
			this->roughness = roughness;
		}
		
		inline float_t getRoughness() const
		{
			return this->roughness;
		}

		inline void setIndexOfRefraction(float_t ior)
		{
			this->ior = ior;
		}

		inline float_t getIndexOfRefraction() const
		{
			return this->ior;
		}

		inline void setTransparency(float_t transparency)
		{
			this->transparency = transparency;
		}

		inline float_t getTransparency() const
		{
			return this->transparency;
		}
	};
}
