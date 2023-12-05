#version 450 core

in vec3 v_TexCoords;

uniform samplerCube u_Skybox;

void main()
{
    gl_FragColor = texture(u_Skybox, v_TexCoords);
}