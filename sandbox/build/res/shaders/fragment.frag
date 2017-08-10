#version 330

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

struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
    float constant;
    float linear;
    float quadratic;
};

in vec2 pass_texCoord;
in vec3 pass_normal;
in vec3 pass_position;

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;


void main()
{
	int albedoBit = (material.shader_parameters & DIFFUSE_BIT) / DIFFUSE_BIT;
	vec3 albedoColor = texture(material.diffuse_map, pass_texCoord).rgb * albedoBit + material.diffuse.rgb * (1 - albedoBit); // Currently not using alpha channel
	int specularBit = (material.shader_parameters & SPECULAR_BIT) / SPECULAR_BIT;
	vec3 specularColor = texture(material.specular_map, pass_texCoord).rgb * specularBit + material.specular * (1 - specularBit);

	vec3 normal = normalize(pass_normal);
	vec3 lightVector = light.position - pass_position;
	vec3 lightDirection = normalize(lightVector);
	float albedoIntensity = max(dot(normal, lightDirection), 0.0f);
	vec3 albedo = albedoIntensity * albedoColor;

	vec3 viewDirection = normalize(cameraPosition - pass_position);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 20);
	vec3 specular = specularIntensity * specularColor;

	float lightDistance = length(lightVector);
	float lightFalloff = 1 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);

	color = vec4((albedo + specular) * lightFalloff * light.intensity * light.color, 1.0f);
}
