#version 330 core
in vec2 TexCoords;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    gl_FragColor = vec4(textColor, texture(text, TexCoords).r);
}