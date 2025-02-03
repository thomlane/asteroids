#pragma once

#include "bsepch.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
				break;
			case GL_UNSIGNED_INT:
				return 4;
				break;
			case GL_UNSIGNED_BYTE:	
				return 1;
				break;
		}
		return -1;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout() : stride(0) {}

	template <typename T> void Push(unsigned int count)
	{
		static_assert(true);
	}

	template <> void Push<float>(unsigned int count)
	{
		VertexBufferElement buffer = { GL_FLOAT, count, false };
		elements.push_back(buffer);
		stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template <> void Push<unsigned int>(unsigned int count)
	{
		VertexBufferElement buffer = { GL_UNSIGNED_INT, count, false };
		elements.push_back(buffer);
		stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template <> void Push<unsigned char>(unsigned int count)
	{
		VertexBufferElement buffer = { GL_UNSIGNED_BYTE, count, true };
		elements.push_back(buffer);
		stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return elements; }
	inline unsigned int GetStride() const { return stride; }
};