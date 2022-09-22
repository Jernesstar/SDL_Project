#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader };

class Shader {
public:
    const std::string Path;
    const ShaderType Type;

public:
    Shader(const std::string& file_path, ShaderType type);
    ~Shader() = default;

    operator int() const { return m_ShaderID; }

private:
    GLint m_ShaderID;
};

}