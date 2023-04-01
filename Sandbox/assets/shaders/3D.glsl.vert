#version 450 core

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjMatrix;

layout(location = 0) in vec3 a_VertexPosition;
layout(location = 1) in vec3 a_Color;

out vec3 v_Color;

void main()
{
    gl_Position = u_ViewProjMatrix * u_ModelMatrix * vec4(a_VertexPosition, 1.0);
    v_Color = a_Color;
}