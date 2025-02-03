#include "bsepch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
	: rendererID(0), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}

void Texture::AttachTexture (std::string& filepath) 
{
	stbi_set_flip_vertically_on_load(true);
	localBuffer = stbi_load(filepath.c_str(), &width, &height, &bitsPerPixel, 4);
	//printf("%d %d %d %s\n", bitsPerPixel, width, height, filepath.c_str());

	if (!localBuffer) 
	{
		printf("\nRead error on file %s:\n  %s\n\n", filepath.c_str(), stbi_failure_reason());
		exit(-1);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(localBuffer);
}

void Texture::Bind(GLuint slot, const std::string& name, const int programId) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->rendererID);
	int loc = glGetUniformLocation(programId, name.c_str());
	glUniform1i(loc, slot);
}

void Texture::Unbind(const int slot) const
{
	glActiveTexture((GLenum)((int)GL_TEXTURE0 + slot));
	glBindTexture(GL_TEXTURE_2D, 0);
}
