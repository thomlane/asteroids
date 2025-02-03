#pragma once

class ShaderProgram
{
private:
	GLuint programId;
	std::vector<Shader> shaders;

public:
	ShaderProgram();
	ShaderProgram(Shader vert, Shader frag);
	~ShaderProgram();

	void AddShader(const GLenum type, const std::string& filePath);
	void AddShader(Shader& shader);
	void AttachShaders();
	void SetUniform1i(const std::string& name, int value);
	inline GLuint GetShaderProgram() { return this->programId; }
	GLint GetUniformLocation(const std::string name);
	GLuint GetAttributeLocation(const std::string name);
	void Use();
	void Unuse();
	void SetUniform4fv(const std::string& name, float v0, float v1, glm::mat4 var);
};