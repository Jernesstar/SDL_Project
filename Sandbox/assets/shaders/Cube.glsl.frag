#version 450 core

in vec3 v_Color;

void main()
{
    gl_FragColor = vec4(v_Color, 1.0);
}