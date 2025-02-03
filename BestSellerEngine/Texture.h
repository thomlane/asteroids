#pragma once
class Texture
{
private:
	GLuint rendererID;
	unsigned char* localBuffer;
	int width, height;
	int bitsPerPixel;
public:
	Texture();
	~Texture();

	void AttachTexture(std::string& filepath);

	void Bind(GLuint slot, const std::string& name, const int programId) const;

	void Unbind(const int slot) const;

	inline int GetWidth () const { return width;  }
	inline int GetHeight() const { return height; }

};

