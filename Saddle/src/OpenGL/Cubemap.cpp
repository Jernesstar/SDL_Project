#include "Cubemap.h"

#include <vector>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Saddle/Core/Utils.h"
#include "Saddle/Core/Log.h"

namespace Saddle {

Cubemap::Cubemap(const std::string& cubemap_folder)
{
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

    std::vector<std::string> faces;


    int width, height;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = Utils::ReadImage(faces[i].c_str(), width, height, true);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
        }
        else
        {
            SADDLE_CORE_LOG_WARNING("Cubemap tex failed to load at path: %s", faces[i].c_str());
        }
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

}