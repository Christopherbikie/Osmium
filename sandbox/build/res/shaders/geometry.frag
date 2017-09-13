#version 330 core

#define DIFFUSE_BIT (1 << 0)
#define AMBIENT_BIT (1 << 1)
#define SPECULAR_BIT (1 << 2)
#define SPECULAR_HIGHLIGHT_BIT (1 << 3)


struct Material
{
	sampler2D diffuse_map;
	sampler2D ambient_map;
	sampler2D specular_map;
	sampler2D highlight_map;

	vec3 ambient;
	vec4 diffuse;
	vec3 specular;
	vec3 highlight;

	int shader_parameters;
};

in vec2 pass_texCoord;
in vec3 pass_normal;
in vec3 pass_position;

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec3 albedo;
layout (location = 3) out vec3 specular;

uniform Material material;

void main()
{
	int albedoBit = (material.shader_parameters & DIFFUSE_BIT) / DIFFUSE_BIT;
	albedo = texture(material.diffuse_map, pass_texCoord).rgb * albedoBit + material.diffuse.rgb * (1 - albedoBit); // Currently not using alpha channel
	int specularBit = (material.shader_parameters & SPECULAR_BIT) / SPECULAR_BIT;
	specular = texture(material.specular_map, pass_texCoord).rgb * specularBit + material.specular * (1 - specularBit);

	position = pass_position;
	normal = normalize(pass_normal);
}
