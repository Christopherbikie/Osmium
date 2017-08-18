#version 330 core

in vec2 pass_texCoord;

out vec4 color;

uniform sampler2D screenTexture;

void main()
{
	color = texture(screenTexture, pass_texCoord);
}
