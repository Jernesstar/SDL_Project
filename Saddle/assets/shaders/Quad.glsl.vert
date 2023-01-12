#version 450 core

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

layout(location = 0) attribute vec3 a_VertexPosition;
layout(location = 1) attribute vec2 a_TextureCoordinate;
layout(location = 2) attribute int a_TextureIndex;

out vec2 v_TextureCoordinate;
out flat float v_TextureIndex;

void main()
{
    mat4 mvp = u_ProjMatrix * u_ViewMatrix;
    gl_Position = mvp * vec4(a_VertexPosition, 1.0);

    v_TextureCoordinate = a_TextureCoordinate;
    v_TextureIndex = a_TextureIndex;
}