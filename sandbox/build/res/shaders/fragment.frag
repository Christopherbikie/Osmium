#version 330

struct Material
{
	sampler2D diffuse_map;
	sampler2D ambient_map;
	sampler2D specular_map;
	sampler2D highlight_map;

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
	vec3 albedoColor = texture(material.diffuse_map, pass_texCoord).rgb;
	vec3 specularColor = texture(material.specular_map, pass_texCoord).rgb;

	vec3 normal = normalize(pass_normal);
	vec3 lightVector = light.position - pass_position;
	vec3 lightDirection = normalize(lightVector);
	float albedoIntensity = max(dot(normal, lightDirection), 0.0f);
	vec3 albedo = albedoIntensity * light.color * albedoColor;

	vec3 viewDirection = normalize(cameraPosition - pass_position);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 20);
	vec3 specular = specularIntensity * light.color * specularColor;

	float lightDistance = length(lightVector);
	float lightFalloff = 1 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);

	color = vec4((albedo + specular) * lightFalloff * light.intensity * light.color, 1.0f);
}
