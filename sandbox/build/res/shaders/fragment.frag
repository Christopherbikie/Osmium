#version 330

struct Material
{
    sampler2D diffuse_map;
    sampler2D ambient_map;
    sampler2D specular_map;
    sampler2D highlight_map;

    int shader_parameters;
};

struct Light {
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


void main()
{
    vec3 lightVector = light.position - pass_position;
    float lightStrength = clamp(dot(normalize(lightVector), normalize(pass_normal)), 0.0f, 1.0f);

    vec4 diffuse_color = texture(material.diffuse_map, pass_texCoord);
    float lightDistance = length(lightVector);

    float lightFalloff = 1 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);

    color = vec4((diffuse_color.xyz * lightStrength * lightFalloff) * light.intensity * light.color, 1.0f);
}