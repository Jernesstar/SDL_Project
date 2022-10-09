#pragma once

#include <string>

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

class Texture2D {
public:
    const std::string Path;
    int Width = 0, Height = 0, BitsPerPixel = 4;
    const unsigned int InternalFormat, DataFormat;

public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(unsigned int slot = 0) const;

    template<typename T, std::size_t TCount>
    void SetData(const T (&data)[TCount])
    {
        uint32_t bpp = DataFormat == GL_RGBA ? 4 : 3;
        SADDLE_CORE_ASSERT(TCount == Width * Height * bpp, "Data must fill entire texture!");
    }

private:
    unsigned int m_TextureID;

    friend class Renderer;
    friend class TextureSystem;
};

}