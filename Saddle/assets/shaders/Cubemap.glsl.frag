#version 450 core

layout(location = 0) in vec3 v_TextureCoordinate;

layout(binding = 0) uniform samplerCube u_Skybox;

void main()
{
    gl_FragColor = texture(u_Skybox, v_TextureCoordinate);
}