#pragma once


class Shader
{
private:
	const GLenum type;
	std::string shaderCode;
	unsigned int rendererID;
	unsigned int shader;

	void CompileShader();
public:
	Shader(const GLenum type, const std::string& shaderCode);
	~Shader();

	std::string ParseShader(const std::string& filePath);
	inline unsigned int GetShader() const { return shader; }
};