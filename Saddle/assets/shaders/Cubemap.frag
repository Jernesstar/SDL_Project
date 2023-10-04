#version 330 core

layout(location = 1) in vec4 v_TextureCoordinate;

layout(binding = 0) uniform samplerCube u_Skybox;

void main()
{    
    gl_FragColor = texture(u_Skybox, v_TextureCoordinate);
}