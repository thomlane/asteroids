#pragma once
class GameObject;

enum class ComponentType
{
	PhysicsBody,
	Input,
	Render
};

class Component
{
public:
	virtual ComponentType GetType() = 0;
	virtual void Update() = 0;

	Component(GameObject* owner) : owner(owner){}
	virtual ~Component() = default;

	GameObject* owner;
};

