#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 colour;

out vec3 pass_colour;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    pass_colour = colour;
}
