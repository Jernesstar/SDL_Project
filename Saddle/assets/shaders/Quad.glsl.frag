#version 450 core

layout(location = 1) in vec2 v_TextureCoordinate;
layout(location = 2) flat in int v_TextureIndex;

layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    vec4 texColor = vec4(0.0, 0.0, 0.0, 0.0);

    switch(v_TextureIndex)
    {
        case  0: texColor = texture(u_Textures[ 0], v_TextureCoordinate); break;
        case  1: texColor = texture(u_Textures[ 1], v_TextureCoordinate); break;
        case  2: texColor = texture(u_Textures[ 2], v_TextureCoordinate); break;
        case  3: texColor = texture(u_Textures[ 3], v_TextureCoordinate); break;
        case  4: texColor = texture(u_Textures[ 4], v_TextureCoordinate); break;
        case  5: texColor = texture(u_Textures[ 5], v_TextureCoordinate); break;
        case  6: texColor = texture(u_Textures[ 6], v_TextureCoordinate); break;
        case  7: texColor = texture(u_Textures[ 7], v_TextureCoordinate); break;
        case  8: texColor = texture(u_Textures[ 8], v_TextureCoordinate); break;
        case  9: texColor = texture(u_Textures[ 9], v_TextureCoordinate); break;
        case 10: texColor = texture(u_Textures[10], v_TextureCoordinate); break;
        case 11: texColor = texture(u_Textures[11], v_TextureCoordinate); break;
        case 12: texColor = texture(u_Textures[12], v_TextureCoordinate); break;
        case 13: texColor = texture(u_Textures[13], v_TextureCoordinate); break;
        case 14: texColor = texture(u_Textures[14], v_TextureCoordinate); break;
        case 15: texColor = texture(u_Textures[15], v_TextureCoordinate); break;
        case 16: texColor = texture(u_Textures[16], v_TextureCoordinate); break;
        case 17: texColor = texture(u_Textures[17], v_TextureCoordinate); break;
        case 18: texColor = texture(u_Textures[18], v_TextureCoordinate); break;
        case 19: texColor = texture(u_Textures[19], v_TextureCoordinate); break;
        case 20: texColor = texture(u_Textures[20], v_TextureCoordinate); break;
        case 21: texColor = texture(u_Textures[21], v_TextureCoordinate); break;
        case 22: texColor = texture(u_Textures[22], v_TextureCoordinate); break;
        case 23: texColor = texture(u_Textures[23], v_TextureCoordinate); break;
        case 24: texColor = texture(u_Textures[24], v_TextureCoordinate); break;
        case 25: texColor = texture(u_Textures[25], v_TextureCoordinate); break;
        case 26: texColor = texture(u_Textures[26], v_TextureCoordinate); break;
        case 27: texColor = texture(u_Textures[27], v_TextureCoordinate); break;
        case 28: texColor = texture(u_Textures[28], v_TextureCoordinate); break;
        case 29: texColor = texture(u_Textures[29], v_TextureCoordinate); break;
        case 30: texColor = texture(u_Textures[30], v_TextureCoordinate); break;
        case 31: texColor = texture(u_Textures[31], v_TextureCoordinate); break;
    }

    gl_FragColor = texColor;
}