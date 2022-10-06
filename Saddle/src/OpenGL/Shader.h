#pragma once

#include <string>

#include "Saddle/Core/Utils.h"

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader };

class Shader {
private:
    class ShaderFile {
    public:
        const ShaderType Type;
        const std::string Path;
        const std::string Source;

        ShaderFile(ShaderType type, const std::string& path);
        ~ShaderFile();

    private:
        unsigned int m_ShaderID;

        friend class Shader;
    };

public:
    ShaderFile VertexShader;
    ShaderFile FragmentShader;

public:
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    operator int() const { return m_ProgramID; } 

private:
    unsigned int m_ProgramID;

private:
    static unsigned int CreateShader(const ShaderFile& file);
};

}