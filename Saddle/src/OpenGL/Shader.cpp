#include "Shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "Saddle/Core/Assert.h"

namespace Saddle {

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
    : VertexShader(ShaderType::VertexShader, vertex_shader),
        FragmentShader(ShaderType::FragmentShader, fragment_shader)
{
    unsigned int shader1 = CreateShader(VertexShader);
    unsigned int shader2 = CreateShader(FragmentShader);

    m_ProgramID = CreateProgram(shader1, shader2);
}

Shader::~Shader() { glDeleteProgram(m_ProgramID); }

void Shader::Bind() const { glUseProgram(m_ProgramID); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetUniformMatrix2(const std::string& name, const glm::mat2& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    this->Bind();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    this->Unbind();
}

void Shader::SetUniformMatrix3(const std::string& name, const glm::mat3& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    this->Bind();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    this->Unbind();
}

void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix)
{
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    this->Bind();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    this->Unbind();
}

unsigned int Shader::CreateShader(const ShaderFile& file)
{
    unsigned int shader_id = glCreateShader(file.Type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

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

        SADDLE_CORE_ASSERT_ARGS(false, "A compile error was detected for shader file %s: %s", file.Path.c_str(), message);
    }

    return shader_id;
}

unsigned int Shader::CreateProgram(unsigned int vertex_shader, unsigned int fragment_shader)
{
    unsigned int program = glCreateProgram();
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
    glDeleteShader(vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(fragment_shader);

    return program;
}

}