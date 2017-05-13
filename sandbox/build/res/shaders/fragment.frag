#version 330

struct Material
{
    sampler2D diffuse_map;
    sampler2D ambient_map;
    sampler2D specular_map;
    sampler2D highlight_map;

    int shader_parameters;
};

in vec2 pass_texCoord;
in vec3 pass_normal;


out vec4 color;

uniform Material material;

void main()
{
    //color = texture(material.diffuse_map, pass_texCoord);
    color = vec4(pass_normal, 1.0f);
}