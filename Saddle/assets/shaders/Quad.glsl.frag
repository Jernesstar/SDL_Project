#version 450 core

layout(location = 1) in vec2 v_TextureCoordinate;

// layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    vec4 texColor = vec4(v_TextureCoordinate, 0.0, 1.0);

    gl_FragColor = texColor;
}