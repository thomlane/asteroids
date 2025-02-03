#pragma once

class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void AddBuffer(const unsigned int* data, unsigned int count);

	void Bind();
	void Unbind();

	inline unsigned int GetCount() const { return count; };
};

