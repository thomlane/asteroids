#include "bsepch.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent(GameObject* owner, Geometry geometry, std::string texturePath)
	:Component(owner), vertexBuffer(VertexBuffer(geometry.vertices.data(), geometry.vertices.size() * sizeof(float)))
{
	vertexArray.AddBuffer(vertexBuffer, geometry.layout);
	indexBuffer.AddBuffer(geometry.indices.data(), geometry.indices.size());
	texture.AttachTexture(texturePath);
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Draw()
{
	vertexArray.Bind();
	indexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}
