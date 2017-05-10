#version 330

in vec2 pass_texCoord;

out vec4 color;

uniform sampler2D diffuse;

void main()
{
    color = vec3(1.0f);
}
