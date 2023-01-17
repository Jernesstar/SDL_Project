#version 450 core

uniform mat4 u_ViewProjMatrix;

layout(location = 0) in vec3 a_VertexPosition;
layout(location = 1) in vec2 a_TextureCoordinate;
layout(location = 2) in int a_TextureIndex;

layout(location = 1) out vec2 v_TextureCoordinate;
layout(location = 2) out flat int v_TextureIndex;

void main()
{
    gl_Position = u_ViewProjMatrix * vec4(a_VertexPosition, 1.0);

    v_TextureCoordinate = a_TextureCoordinate;
    v_TextureIndex = a_TextureIndex;
}