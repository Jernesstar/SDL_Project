#include "Shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "Saddle/Core/Assert.h"

namespace Saddle {

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
    : VertexShader(ShaderType::VertexShader, vertex_shader),
        FragmentShader(ShaderType::FragmentShader, fragment_shader)
{
    uint32_t shader1 = CreateShader(VertexShader);
    uint32_t shader2 = CreateShader(FragmentShader);

    m_ProgramID = CreateProgram(shader1, shader2);
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
    uint32_t shader_id = glCreateShader(file.Type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    const char* address = file.Source.c_str();
    // Setting the data of the shader, setting last value to nullptr will use the whole shader_text
    glShaderSource(shader_id, 1, &address, nullptr);
    glCompileShader(shader_id); // Compiling the shader

    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result); // Getting the compile status, whether or not the shader compiled

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length); // Get the length of the error message
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message); // Get the error message

        SADDLE_CORE_ASSERT_ARGS(false, "A compile error was detected for shader file %s:\n%s", file.Path.c_str(), message);
    }

    return shader_id;
}

uint32_t Shader::CreateProgram(uint32_t vertex_shader, uint32_t fragment_shader)
{
    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if(result == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        SADDLE_CORE_ASSERT(false, "Shader linking failed");

        glDeleteProgram(program);
    }

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

}