#pragma once

#include <string>
#include <cstdint>

#include "VertexArray.h"

namespace Saddle {

class Cubemap {
public:
    Cubemap(const std::string& cubemap_folder);
    Cubemap(const std::vector<std::string>& faces);

    void Bind() const;

    uint32_t GetTextureID() const { return m_TextureID; }

private:
    uint32_t m_TextureID;
};

}