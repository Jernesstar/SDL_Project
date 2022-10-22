#version 330 core

in vec2 v_TextureCoordinate;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TextureCoordinate);
    gl_FragColor = texColor;
}