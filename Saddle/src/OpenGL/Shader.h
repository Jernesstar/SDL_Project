#pragma once

#include <iostream>

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
    ~Shader();

    operator int() { return m_ShaderID; }

private:
    GLint m_ShaderID;

private:
    static std::string Load(const std::string& file_path);
};

}