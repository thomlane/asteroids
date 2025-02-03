#pragma once

class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};