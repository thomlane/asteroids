#include "bsepch.h"

ShaderProgram::ShaderProgram()
{
	this->programId = glCreateProgram();
}

ShaderProgram::ShaderProgram(Shader vert, Shader frag)
{
	this->programId = glCreateProgram();
	this->AddShader(vert);
	this->AddShader(frag);
	this->AttachShaders();

}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::AddShader(const GLenum type, const std::string& filePath)
{
	Shader shader(type, filePath);
	shaders.push_back(shader);
}

void ShaderProgram::AddShader(Shader& shader)
{
	shaders.push_back(shader);
}

void ShaderProgram::AttachShaders()
{
	for (Shader& shader : shaders)
	{
		glAttachShader(this->programId,shader.GetShader());
	}


	glLinkProgram(this->programId);

	int status;
	glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
	// If link failed, get and print log
	if (status != 1) {
		int length;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
		char* buffer = new char[length];
		glGetProgramInfoLog(programId, length, NULL, buffer);
		printf("Link log:\n%s\n", buffer);
		delete buffer;
	}
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform4fv(const std::string& name, float v0, float v1, glm::mat4 var)
{
	glUniformMatrix4fv(GetUniformLocation(name), v0, v1, &var[0][0]);
}

GLint ShaderProgram::GetUniformLocation(const std::string name)
{
	return glGetUniformLocation(this->programId, name.c_str());
}

GLuint ShaderProgram::GetAttributeLocation(const std::string name)
{
	
	return glGetAttribLocation(this->programId,name.c_str());
}

void ShaderProgram::Use()
{
	glUseProgram(this->programId);
}
void ShaderProgram::Unuse()
{
	glUseProgram(0);
}
