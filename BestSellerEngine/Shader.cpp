#include "bsepch.h"

static void getShaderCompilationError(GLuint shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::Shader(const GLenum type, const std::string& filePath) 
    : type(type), shaderCode(ParseShader(filePath)), rendererID(0)
{
    CompileShader();
}

Shader::~Shader()
{
    //glDeleteShader(this->shader);
}

std::string Shader::ParseShader(const std::string& filePath)
{
    std::ifstream shaderFile (filePath);
    std::stringstream shaderStream;

    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    else {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
    }
    return shaderStream.str();
}

void Shader::CompileShader()
{
    this->shader = glCreateShader(this->type);
    const char* src = this->shaderCode.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    getShaderCompilationError(shader);

    // Get the compilation status
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // If compilation status is not OK, get and print the log message.
    if (status != 1) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* buffer = new char[length];
        glGetShaderInfoLog(shader, length, NULL, buffer);
        printf("Compile log %s\n", buffer);
        delete buffer;
    }
}
