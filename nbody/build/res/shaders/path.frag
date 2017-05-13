#version 330

flat in int pass_alpha;

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, pass_alpha);
}
