#version 330 core

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

layout(location = 0) attribute vec3 a_VertexPosition;
layout(location = 1) attribute vec3 a_Color;

out vec3 v_Color;

void main()
{
    mat4 mvp = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix;
    gl_Position = mvp * vec4(a_VertexPosition, 1.0);
    v_Color = a_Color;
}