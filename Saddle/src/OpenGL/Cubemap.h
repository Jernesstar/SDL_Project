#pragma once

#include <string>
#include <filesystem>

namespace Saddle {

class Cubemap {
public:
    Cubemap(const std::string& cubemap_folder);

private:
    uint32_t m_TextureID;
};

}