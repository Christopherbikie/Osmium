#version 330

in vec3 pass_colour;

out vec4 color;

void main()
{
    color = vec4(pass_colour, 1.0);
}
