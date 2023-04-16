#version 450 core

layout(location = 0) in vec2 v_TextureCoordinate;
layout(location = 1) in vec3 v_Normal;

layout(binding = 0) uniform sampler2D u_Texture;

void main()
{
    gl_FragColor = texture(u_Texture, v_TextureCoordinate);
}