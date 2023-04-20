#pragma once

#include "BufferLayout.h"

namespace Saddle {

class UniformBuffer {
public:
    const BufferLayout Layout;
    const uint32_t Binding;

public:
    UniformBuffer(const BufferLayout& layout, uint32_t binding);
    ~UniformBuffer();

    void SetData(uint32_t offset, uint32_t size, const void* data);
    void SetData(const std::string& name, const void* data);

private:
    uint32_t m_BufferID;
};

}