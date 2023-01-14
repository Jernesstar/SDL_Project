#version 450 core

layout(location = 1) in vec2 v_TextureCoordinate;
layout(location = 2) in flat float v_TextureIndex;

// layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    vec4 texColor = vec4(0, 0, 0, 0);

    gl_FragColor = texColor;
}