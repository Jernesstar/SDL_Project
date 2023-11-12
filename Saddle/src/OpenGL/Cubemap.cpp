#include "Cubemap.h"

#include <vector>
#include <unordered_map>
#include <filesystem>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Saddle/Core/Utils.h"
#include "Saddle/Core/Log.h"

namespace Saddle {

std::vector<std::Path> GetImagePaths(const std::string& folder)
{
    std::vector<std::string> paths;
    for(const auto& p : std::filesystem::directory_iterator(folder.c_str()))
    {
        if(p.path().extension() == ".jpg" || p.path().extension() == ".jpeg" || p.path().extension() == ".png")
            paths.push_back(p.path().string());
        
        if(paths.size() == 6)
            break;
    }

    if(paths.size() < 6)
        SADDLE_CORE_LOG_WARNING("Cubemap folder %s does not have at least 6 images", folder.c_str());
    return paths;
}

Cubemap::Cubemap(const std::string& cubemap_folder)
{
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);

    std::vector<std::Path> faces = GetImagePaths(cubemap_folder);
    std::unordered_map<std::string, int> map =
    {
        { "right", 0 }, { "left", 1 }, { "top", 2 }, { "bottom", 3 }, { "front", 4 }, { "back", 5 }
    };

    int width, height;
    for(auto& face : faces)
    {
        unsigned char* data = Utils::ReadImage(face.path().c_str(), width, height, true);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + map[face.path().name()], 0, GL_RGB, width,
                height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            SADDLE_CORE_LOG_WARNING("Could not load image: %s", face.c_str());
        }
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Cubemap::Bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
}

}