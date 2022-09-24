#pragma once

#include <string>

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader };

class Shader {
public:
    const std::string Path;
    const ShaderType Type;

public:
    Shader(const std::string& file_path, ShaderType type);
    ~Shader();

    operator int() const { return m_ShaderID; }

private:
    unsigned int m_ShaderID;
};

}