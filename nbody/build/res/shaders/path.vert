#version 330

layout (location = 0) in vec3 position;

flat out int pass_alpha;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0f);

    if (position == vec3(0.0f))
        pass_alpha = 0;
    else
        pass_alpha = 1;
}