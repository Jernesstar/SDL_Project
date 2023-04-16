#version 450 core

uniform vec3 u_LightColor;

void main()
{
    gl_FragColor = vec4(u_LightColor, 1.0);
}