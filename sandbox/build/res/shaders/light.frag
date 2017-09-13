#version 330 core

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

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D specular;

uniform Light light;
uniform vec3 cameraPosition;

void main()
{
	vec3 fragPosition = texture(position, pass_texCoord).xyz;
	vec3 fragNormal = texture(normal, pass_texCoord).xyz;
	vec3 fragAlbedo = texture(albedo, pass_texCoord).rgb;
	vec3 fragSpecular = texture(specular, pass_texCoord).rgb;

	vec3 lightVector = light.position - fragPosition;
	vec3 lightDirection = normalize(lightVector);
	float albedoIntensity = max(dot(fragNormal, lightDirection), 0.0f);
	vec3 albedoFinal = albedoIntensity * fragAlbedo;

	vec3 viewDirection = normalize(cameraPosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, fragNormal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 20);
	vec3 specularFinal = specularIntensity * fragSpecular;

	float lightDistance = length(lightVector);
	float lightFalloff = 1 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);

	gl_FragColor = vec4((albedoFinal + specularFinal) * lightFalloff * light.intensity * light.color, 1.0f);
}
