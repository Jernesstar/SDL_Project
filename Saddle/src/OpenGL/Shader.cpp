#include "Shader.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

Shader::ShaderFile::ShaderFile(ShaderType type, const std::string& path)
    : Type(type), Path(path), Source(Utils::LoadFile(path)) { m_ShaderID = Shader::CreateShader(*this); }

Shader::ShaderFile::~ShaderFile() { glDeleteShader(m_ShaderID); }

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
    : VertexShader(ShaderType::VertexShader, vertex_shader), FragmentShader(ShaderType::FragmentShader, fragment_shader)
{
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, VertexShader.m_ShaderID);
    glAttachShader(m_ProgramID, FragmentShader.m_ShaderID);
    glLinkProgram(m_ProgramID);
    glValidateProgram(m_ProgramID);
}

Shader::~Shader() { glDeleteProgram(m_ProgramID); }

void Shader::Bind() const { glUseProgram(m_ProgramID); }
void Shader::Unbind() const { glUseProgram(0); }

unsigned int Shader::CreateShader(const ShaderFile& shader_file)
{
    unsigned int shader_id = glCreateShader(shader_file.Type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    const char* address = shader_file.Source.c_str();
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

        SADDLE_CORE_ASSERT_ARGS(false, "A compile error was detected for shader file %s: %s", shader_file.Path.c_str(), message);
    }

    return shader_id;
}

}