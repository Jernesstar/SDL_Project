#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Saddle {

enum class ShaderType { VertexShader, FragmentShader, ComputeShader };

class Shader {
public:
    struct ShaderFile {
        const ShaderType Type;
        const std::string Path;
    };

public:
    Shader(const std::initializer_list<ShaderFile>& files);
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
    std::vector<ShaderFile> m_ShaderFiles;

private:
    uint32_t CreateShader(const ShaderFile& file);
    void CreateProgram();
};

}