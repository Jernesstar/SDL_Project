#version 450 core

layout(location = 0) in vec2 v_TextureCoordinate;
layout(location = 1) in vec3 v_Normal;

layout(binding = 0) uniform sampler2D v_Diffuse;
layout(binding = 1) uniform sampler2D v_Specular;

void main()
{
    float specular_intensity = 0.5;
    vec4 diffuse_color = texture(v_Diffuse, v_TextureCoordinate);
    vec4 specular_color = texture(v_Specular, v_TextureCoordinate);

    gl_FragColor = diffuse_color * specular_color;
}