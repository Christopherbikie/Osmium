#version 330

flat in int pass_alpha;

out vec4 color;

uniform vec3 pathColour;

void main()
{
    color = vec4(pathColour, pass_alpha);
}
