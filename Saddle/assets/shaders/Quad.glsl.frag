#version 450 core

in vec2 v_TextureCoordinate;
in flat float v_TextureIndex;

layout(binding = 0) uniform sampler2D u_Texture[32];

void main()
{
    vec4 texColor = vec4(0, 0, 0, 0);
    switch(int(v_TextureIndex))
    {
        case 0:
            texColor = texture(u_Texture[0], v_TextureCoordinate); break;
        case 1:
            texColor = texture(u_Texture[1], v_TextureCoordinate); break;
        case 2:
            texColor = texture(u_Texture[2], v_TextureCoordinate); break;
        case 3:
            texColor = texture(u_Texture[3], v_TextureCoordinate); break;
        case 4:
            texColor = texture(u_Texture[4], v_TextureCoordinate); break;
        case 5:
            texColor = texture(u_Texture[5], v_TextureCoordinate); break;
        case 6:
            texColor = texture(u_Texture[6], v_TextureCoordinate); break;
        case 7:
            texColor = texture(u_Texture[7], v_TextureCoordinate); break;
        case 8:
            texColor = texture(u_Texture[8], v_TextureCoordinate); break;
        case 9:
            texColor = texture(u_Texture[9], v_TextureCoordinate); break;
        case 10:
            texColor = texture(u_Texture[10], v_TextureCoordinate); break;
        case 11:
            texColor = texture(u_Texture[11], v_TextureCoordinate); break;
        case 12:
            texColor = texture(u_Texture[12], v_TextureCoordinate); break;
        case 13:
            texColor = texture(u_Texture[13], v_TextureCoordinate); break;
        case 14:
            texColor = texture(u_Texture[14], v_TextureCoordinate); break;
        case 15:
            texColor = texture(u_Texture[15], v_TextureCoordinate); break;
        case 16:
            texColor = texture(u_Texture[16], v_TextureCoordinate); break;
        case 17:
            texColor = texture(u_Texture[17], v_TextureCoordinate); break;
        case 18:
            texColor = texture(u_Texture[18], v_TextureCoordinate); break;
        case 19:
            texColor = texture(u_Texture[19], v_TextureCoordinate); break;
        case 20:
            texColor = texture(u_Texture[20], v_TextureCoordinate); break;
        case 21:
            texColor = texture(u_Texture[21], v_TextureCoordinate); break;
        case 22:
            texColor = texture(u_Texture[22], v_TextureCoordinate); break;
        case 23:
            texColor = texture(u_Texture[23], v_TextureCoordinate); break;
        case 24:
            texColor = texture(u_Texture[24], v_TextureCoordinate); break;
        case 25:
            texColor = texture(u_Texture[25], v_TextureCoordinate); break;
        case 26:
            texColor = texture(u_Texture[26], v_TextureCoordinate); break;
        case 27:
            texColor = texture(u_Texture[27], v_TextureCoordinate); break;
        case 28:
            texColor = texture(u_Texture[28], v_TextureCoordinate); break;
        case 29:
            texColor = texture(u_Texture[29], v_TextureCoordinate); break;
        case 30:
            texColor = texture(u_Texture[30], v_TextureCoordinate); break;
        case 31:
            texColor = texture(u_Texture[31], v_TextureCoordinate); break;
    }

    gl_FragColor = texColor;
}