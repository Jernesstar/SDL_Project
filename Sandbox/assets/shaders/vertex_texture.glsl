#version 330 core

uniform mat4 u_MVP;

layout(location = 0) attribute vec2 a_VertexPosition;
layout(location = 1) attribute vec2 a_TextureCoordinate;

out vec2 v_TextureCoordinate;

void main()
{
    gl_Position = u_MVP * vec4(a_VertexPosition, 1.0, 1.0);
    v_TextureCoordinate = a_TextureCoordinate;
}