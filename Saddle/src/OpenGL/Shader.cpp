#include "Shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Utils.h"

namespace Saddle {

Shader::Shader(const std::initializer_list<ShaderFile>& files)
    : m_ShaderFiles(files)
{
    CreateProgram();
}

Shader::~Shader() { glDeleteProgram(m_ProgramID); }

void Shader::Bind() const { glUseProgram(m_ProgramID); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetUniformInt(const std::string& name, int _int)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniform1i(location, _int);
}

void Shader::SetUniformFloat(const std::string& name, float _float)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniform1f(location, _float);
}

void Shader::SetUniformVec2(const std::string& name, const glm::vec2& vec)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniform2f(location, vec.x, vec.y);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vec)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& vec)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniform4f(location, vec.r, vec.g, vec.b, vec.a);
}

void Shader::SetUniformMatrix2(const std::string& name, const glm::mat2& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformMatrix3(const std::string& name, const glm::mat3& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

uint32_t Shader::CreateShader(const ShaderFile& file)
{
    uint32_t type;
    if(file.Type == ShaderType::VertexShader)
        type = GL_VERTEX_SHADER;
    if(file.Type == ShaderType::FragmentShader)
        type = GL_FRAGMENT_SHADER;
    if(file.Type == ShaderType::ComputeShader)
        type = GL_COMPUTE_SHADER;

    uint32_t shader_id = glCreateShader(type);

    std::string source = Utils::ReadFile(file.Path);
    const char* address = source.c_str();
    glShaderSource(shader_id, 1, &address, nullptr);
    glCompileShader(shader_id);

    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);

        SADDLE_CORE_ASSERT_ARGS(false, "A compile error was detected for shader file at %s:\n%s", file.Path.c_str(), message);
    }

    return shader_id;
}

void Shader::CreateProgram()
{
    uint32_t program = glCreateProgram();
    std::vector<uint32_t> shader_ids(m_ShaderFiles.size());

    for(const auto& shader : m_ShaderFiles)
    {
        uint32_t shader_id = CreateShader(shader);
        glAttachShader(program, shader_id);
        shader_ids.push_back(shader_id);
    }

    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if(result == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);

        SADDLE_CORE_ASSERT_ARGS(false, "An error occured while linking %s: \n%s", message);

        glDeleteProgram(program);
        return;
    }

    for(const auto& shader_id : shader_ids)
    {
        glDetachShader(program, shader_id);
        glDeleteShader(shader_id);
    }

    m_ProgramID = program;
}

}