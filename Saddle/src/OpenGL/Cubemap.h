#pragma once

#include <string>
#include <cstdint>

namespace Saddle {

class Cubemap {
public:
    Cubemap(const std::string& cubemap_folder);

    void Bind() const;

private:
    uint32_t m_TextureID;
};

}