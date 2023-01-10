#version 330 core

in vec2 v_TextureCoordinate;
in int v_TextureIndex;

uniform sampler2D[32] u_Texture;

void main()
{
    vec4 texColor = vec4(0, 0, 0, 0);
    switch(v_TextureIndex)
    {
        case 1:
            texture = texture(u_Texture[1], v_TextureCoordinate); 
        case 2:
            texture = texture(u_Texture[2], v_TextureCoordinate); 
        case 3:
            texture = texture(u_Texture[3], v_TextureCoordinate); 
        case 4:
            texture = texture(u_Texture[4], v_TextureCoordinate); 
        case 5:
            texture = texture(u_Texture[5], v_TextureCoordinate); 
        case 6:
            texture = texture(u_Texture[6], v_TextureCoordinate); 
        case 7:
            texture = texture(u_Texture[7], v_TextureCoordinate); 
        case 8:
            texture = texture(u_Texture[8], v_TextureCoordinate); 
        case 9:
            texture = texture(u_Texture[9], v_TextureCoordinate); 
        case 10:
            texture = texture(u_Texture[10], v_TextureCoordinate); 
        case 11:
            texture = texture(u_Texture[11], v_TextureCoordinate); 
        case 12:
            texture = texture(u_Texture[12], v_TextureCoordinate); 
        case 13:
            texture = texture(u_Texture[13], v_TextureCoordinate); 
        case 14:
            texture = texture(u_Texture[14], v_TextureCoordinate); 
        case 15:
            texture = texture(u_Texture[15], v_TextureCoordinate); 
        case 16:
            texture = texture(u_Texture[16], v_TextureCoordinate); 
        case 17:
            texture = texture(u_Texture[17], v_TextureCoordinate); 
        case 18:
            texture = texture(u_Texture[18], v_TextureCoordinate); 
        case 19:
            texture = texture(u_Texture[19], v_TextureCoordinate); 
        case 20:
            texture = texture(u_Texture[20], v_TextureCoordinate); 
        case 21:
            texture = texture(u_Texture[21], v_TextureCoordinate); 
        case 22:
            texture = texture(u_Texture[22], v_TextureCoordinate); 
        case 23:
            texture = texture(u_Texture[23], v_TextureCoordinate); 
        case 24:
            texture = texture(u_Texture[24], v_TextureCoordinate); 
        case 25:
            texture = texture(u_Texture[25], v_TextureCoordinate); 
        case 26:
            texture = texture(u_Texture[26], v_TextureCoordinate); 
        case 27:
            texture = texture(u_Texture[27], v_TextureCoordinate); 
        case 28:
            texture = texture(u_Texture[28], v_TextureCoordinate); 
        case 29:
            texture = texture(u_Texture[29], v_TextureCoordinate); 
        case 30:
            texture = texture(u_Texture[30], v_TextureCoordinate); 
        case 31:
            texture = texture(u_Texture[31], v_TextureCoordinate); 
    }

    gl_FragColor = texColor;
}