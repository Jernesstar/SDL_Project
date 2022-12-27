#pragma once

#include <string>

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

class Texture2D {
public:
    int32_t Width = 0, Height = 0, BitsPerPixel = 4;
    const uint32_t InternalFormat, DataFormat;

public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(uint32_t slot = 0);
    void SetData(const std::string& path);

    const std::string& GetPath() { return m_Path; }

    operator int32_t() const { return m_Slot; }

private:
    uint32_t m_TextureID;
    int32_t m_Slot;

    std::string m_Path;
};

}