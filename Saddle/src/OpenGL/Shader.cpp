#include "Shader.h"

#include <glad/glad.h>

namespace Saddle {

int ConvertType(const ShaderType& type) { return type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER; }

Shader::Shader(const std::string& file_path, ShaderType type)
    : Path(file_path), Type(type), ShaderID(glCreateShader(ConvertType(type)))
{
    std::string shader_text = Load(file_path);
    
    const char* address = shader_text.c_str();
    glShaderSource(ShaderID, 1, &address, NULL);
    glCompileShader(ShaderID);
}

Shader::~Shader()
{
    
}

}