#pragma once
#include <cmath>
#include <string>
#include "../graphics/Texture.h"

namespace os
{
	class Material
	{
	private:
		float_t albedo[4];
		float_t specular[4];
		float_t transmittance[4];
		float_t emission[4];
		float_t roughness;
		float_t ior;
		float_t transparency;
	
		bool hasTransparency = false;

		Texture albedoMap;
		Texture normalMap;
		Texture specularMap;
		Texture heightMap;
		Texture emissionMap;
	public:
		void setAlbedo(float_t r, float_t g, float_t b, float_t a)
		{
			this->emission[0] = r;
			this->emission[1] = g;
			this->emission[2] = b;
			this->emission[4] = a;
		}

		void setSpecular(float_t r, float_t g, float_t b, float_t a)
		{
			this->emission[0] = r;
			this->emission[1] = g;
			this->emission[2] = b;
			this->emission[4] = a;
		}

		void setTransmittance(float_t r, float_t g, float_t b, float_t a)
		{
			this->emission[0] = r;
			this->emission[1] = g;
			this->emission[2] = b;
			this->emission[4] = a;
		}

		void setEmission(float_t r, float_t g, float_t b, float_t a)
		{
			this->emission[0] = r;
			this->emission[1] = g;
			this->emission[2] = b;
			this->emission[4] = a;
		}

		void setRoughness(float_t roughness)
		{
			this->roughness = roughness;
		}
		
		void setIndexOfRefraction(float_t ior)
		{
			this->ior = ior;
		}

		void setTransparency(float_t transparency)
		{
			this->transparency = transparency;
		}
		
		void loadAlbedoMap(std::string texture_path);
		void unloadAlbedoMap();

		void loadNormalMap(std::string texture_path);
		void unloadNormalMap();

		void loadSpecularMap(std::string texture_path);
		void unloadSpecularMap();

		void loadHeightMap(std::string texture_path);
		void unloadHeightMap();

		void loadEmissionMap(std::string texture_path);
		void unloadEmissionMap();
	};
}
