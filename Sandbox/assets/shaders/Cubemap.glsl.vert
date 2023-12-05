#version 450 core

layout(location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_ViewProj;

void main()
{
    gl_Position = u_ViewProj * vec4(a_Position, 1.0);
    v_TexCoords = a_Position;
}