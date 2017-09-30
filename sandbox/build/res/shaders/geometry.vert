#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 pass_position;
out vec2 pass_texCoord;
out vec3 pass_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	gl_Position = projection * view * worldPosition;
	pass_position = worldPosition.xyz;
	pass_texCoord = texCoord;
	pass_normal = normalMat * normal;
}
