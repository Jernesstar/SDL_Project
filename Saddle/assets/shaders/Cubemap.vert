#version 450 core

uniform mat4 u_ViewProjMatrix;

layout (location = 0) in vec3 a_VertexPosition;

layout(location = 0) out vec3 v_TextureCoordinate;

void main()
{
    gl_Position = u_ViewProjMatrix * vec4(a_VertexPosition, 1.0);
    v_TextureCoordinate = a_VertexPosition;
}