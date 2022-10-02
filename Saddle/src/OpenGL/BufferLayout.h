#pragma once

#include <vector>
#include <string>

namespace Saddle {

enum class BufferElementType {
    Float, Int, Vec2, Vec3, Vec4, Mat2, Mat3, Mat4
};

static int BufferElementSize(BufferElementType type)
{
    switch(type)
    {
        case BufferElementType::Float: return 4;
        case BufferElementType::Int:   return 4;
        case BufferElementType::Vec2:  return 4 * 2;
        case BufferElementType::Vec3:  return 4 * 3;
        case BufferElementType::Vec4:  return 4 * 4;
        case BufferElementType::Mat2:  return 4 * 2 * 2;
        case BufferElementType::Mat3:  return 4 * 3 * 3;
        case BufferElementType::Mat4:  return 4 * 4 * 4;
    }
    return 0;
}

static int BufferElementCount(BufferElementType type)
{
    switch(type)
    {
        case BufferElementType::Float: return 1;
        case BufferElementType::Int:   return 1;
        case BufferElementType::Vec2:  return 2;
        case BufferElementType::Vec3:  return 3;
        case BufferElementType::Vec4:  return 4;
        case BufferElementType::Mat2:  return 2; // 2 * Vec2
        case BufferElementType::Mat3:  return 3; // 3 * Vec3
        case BufferElementType::Mat4:  return 4; // 4 * Vec4
    }
    return 0;
}

struct BufferElement {
    const std::string Name;
    const BufferElementType Type;
    const int Size;
    const int ComponentCount;
    const bool Normalized;

    BufferElement(const std::string& name, BufferElementType type, bool normalized = true)
        : Name(name), Type(type), Size(BufferElementSize(type)), ComponentCount(BufferElementCount(type)),
            Normalized(normalized) { }
};

class BufferLayout {
public:
    const std::vector<BufferElement> Elements;
    const int Stride;

public:
    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : Elements(elements), Stride(CalculateStride(elements)) { }

    std::vector<BufferElement>::const_iterator begin() const { return Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return Elements.end(); }

private:
    int CalculateStride(const std::initializer_list<BufferElement>& elements)
    {
        int stride = 0;
        for(auto& element : elements)
            stride += element.Size;
        return stride;
    }
};

}