#version 330 core

in vec2 v_TextureCoordinate;

uniform sampler2D u_Texture;
uniform vec3 textColor;

void main()
{
    vec4 texColor = vec4(textColor, texture(u_Texture, v_TextureCoordinate).r);
    gl_FragColor = texColor;
}