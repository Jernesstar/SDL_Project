#include "Shader.h"

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Utils.h"

namespace Saddle {

Shader::Shader(const std::string& file_path, ShaderType type)
    : Path(file_path), Type(type)
{
    m_ShaderID = glCreateShader(type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    
    std::string shader_text = Utils::LoadFile(file_path);
    const char* address = shader_text.c_str();
    
    // Setting the data of the shader, setting last value to nullptr will use the whole shader_text
    glShaderSource(m_ShaderID, 1, &address, NULL); // Compiling the shader
    glCompileShader(m_ShaderID);

    int result;
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result); // Getting the compile status, whether or not the shader compiled

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length); // Get the length of the error message
        char* message = (char*)(alloca(length * sizeof(char)));
        glGetShaderInfoLog(m_ShaderID, length, &length, message); // Get the error message

        SADDLE_CORE_ASSERT_ARGS(false, "A compile error was detected for shader file %s: %s", file_path.c_str(), message);
    }
}

}