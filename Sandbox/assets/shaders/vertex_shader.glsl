#version 330 core

uniform mat4 MVP;
layout(location = 0) attribute vec2 vPos;
layout(location = 1) attribute vec3 vCol;
varying vec3 color;

void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
}