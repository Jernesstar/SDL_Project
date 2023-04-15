#version 450 core

uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

void main()
{
    gl_FragColor = vec4(u_LightColor * u_ObjectColor, 1.0);
}