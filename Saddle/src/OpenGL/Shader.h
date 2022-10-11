#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include "Saddle/Core/Utils.h"

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader };

class Shader {
private:
    struct ShaderFile {
        const ShaderType Type;
        const std::string Path;
        const std::string Source;

        ShaderFile(ShaderType type, const std::string& path)
            : Type(type), Path(path), Source(Utils::LoadFile(path)) { }
    };

public:
    ShaderFile VertexShader;
    ShaderFile FragmentShader;

public:
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniformInt(const std::string& name, int _int);
    void SetUniformFloat(const std::string& name, float _float);

    void SetUniformVec2(const std::string& name, const glm::vec2& vec);
    void SetUniformVec3(const std::string& name, const glm::vec3& vec);
    void SetUniformVec4(const std::string& name, const glm::vec4& vec);

    void SetUniformMatrix2(const std::string& name, const glm::mat2& matrix);
    void SetUniformMatrix3(const std::string& name, const glm::mat3& matrix);
    void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix);

    operator uint32_t() const { return m_ProgramID; } 

private:
    uint32_t m_ProgramID;

private:
    static uint32_t CreateShader(const ShaderFile& shader_file);
    static uint32_t CreateProgram(uint32_t vertex_shader, uint32_t fragment_shader);
};

}