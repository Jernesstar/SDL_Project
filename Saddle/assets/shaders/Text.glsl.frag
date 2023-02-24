#version 450 core

layout(location = 1) in vec2 v_TextureCoordinate;
layout(location = 2) flat in int v_TextureIndex;

layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    gl_FragColor = vec4(vec3(1.0, 1.0, 1.0), texture(u_Textures[v_TextureIndex], v_TextureCoordinate).r);
}