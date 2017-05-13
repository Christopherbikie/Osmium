#pragma once
#include <cmath>
#include <string>
#include "../graphics/Texture.h"
#include "../graphics/Shader.h"
//#include <tiny_obj_loader.h>
#include <array>
#include <memory>

namespace os
{
	class Material
	{
	private:
		std::array<float_t, 4> albedo;
		std::array<float_t, 4> specular;
		std::array<float_t, 4> transmittance;
		std::array<float_t, 4> emission;
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
		void setDiffuseMap(Texture diffuse);
		std::shared_ptr<Texture> getDiffuseMap();

		void setAmbientMap(std::string ambient);
		void setAmbientMap(Texture ambient);
		std::shared_ptr<Texture> getAmbientMap();

		void setSpecularMap(std::string specular);
		void setSpecularMap(Texture specular);
		std::shared_ptr<Texture> getSpecularMap();
		
		void setSpecularHighlightsMap(std::string highlights);
		void setSpecularHighlightsMap(Texture highlights);
		std::shared_ptr<Texture> getSpecularHighlightsMap();

		void bind(Shader* shader);
		void unbind();

		inline void setAlbedo(float_t r, float_t g, float_t b, float_t a)
		{
			this->albedo[0] = r;
			this->albedo[1] = g;
			this->albedo[2] = b;
			this->albedo[4] = a;
		}

		inline const std::array<float_t, 4>& getAlbedo() const
		{
			return this->albedo;
		}
		
		inline void setSpecular(float_t r, float_t g, float_t b, float_t a)
		{
			this->specular[0] = r;
			this->specular[1] = g;
			this->specular[2] = b;
			this->specular[4] = a;
		}

		inline const std::array<float_t, 4>& getSpecular() const
		{
			return this->specular;
		}

		inline void setTransmittance(float_t r, float_t g, float_t b, float_t a)
		{
			this->transmittance[0] = r;
			this->transmittance[1] = g;
			this->transmittance[2] = b;
			this->transmittance[4] = a;
		}

		inline const std::array<float_t, 4>& getTransmittance() const
		{
			return this->transmittance;
		}

		inline void setEmission(float_t r, float_t g, float_t b, float_t a)
		{
			this->emission[0] = r;
			this->emission[1] = g;
			this->emission[2] = b;
			this->emission[4] = a;
		}

		inline const std::array<float_t, 4>& getEmission() const
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
