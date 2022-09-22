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
}

}