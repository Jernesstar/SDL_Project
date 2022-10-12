#pragma once

#include <string>

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

class Texture2D {
public:
    const std::string Path;
    int32_t Width = 0, Height = 0, BitsPerPixel = 4;
    const uint32_t InternalFormat, DataFormat;

public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(uint32_t slot = 0);

    operator uint32_t() const { return m_Slot; }

private:
    uint32_t m_TextureID;
    uint32_t m_Slot;

    friend class Renderer;
    friend class TextureSystem;
};

}