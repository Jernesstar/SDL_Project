#version 330 core

uniform mat4 u_MVP;
layout(location = 0) attribute vec2 a_VertexPosition;
layout(location = 1) attribute vec3 a_VertexColor;
out vec4 o_Color;

void main()
{
    gl_Position = u_MVP * vec4(a_VertexPosition, 1.0, 1.0);
    o_Color = vec4(a_VertexColor, 1.0);
}