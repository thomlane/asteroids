#pragma once
#include "Component.h"

class RenderComponent :
    public Component
{
public:
	VertexBuffer vertexBuffer;
	VertexArray vertexArray;
	IndexBuffer indexBuffer;
	Texture texture;

	inline void Update() {};

	inline ComponentType GetType() override { return ComponentType::Render; }

	RenderComponent(GameObject* owner, Geometry geometry, std::string texturePath);
	~RenderComponent();
	void Draw();
};

