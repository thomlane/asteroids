#include "bsepch.h"
#include "PlayerInputComponent.h"

void GameObject::Update()
{
	for (Component* component : componentList)
	{
		component->Update();
	}
	transform.Update();
	lifeTimer += BSEWindowHandler::GetInstance()->deltaTime;
}

void GameObject::Scale(float mult)
{
	transform.scale *= mult;
	this->FindComponent<PhysicsBodyComponent>()->ScaleShape(mult);
}

GameObject::GameObject(std::string name, glm::vec3 position, float rotation)
	: name(name), lifeTimer(0)
{
	transform.position = position;
	transform.rotation.z = rotation;
	transform.Update();
	eventListener = new EventListener();
}

GameObject::GameObject(std::string name,glm::vec3 position)
	: name(name), lifeTimer(0)
{
	transform.position = position;
	transform.Update();
	eventListener = new EventListener();
}

GameObject::GameObject(std::string name)
	: GameObject(name,glm::vec3(0))
{}

GameObject::~GameObject()
{
	for (Component* component : componentList)
	{
		delete(component);
	}
	componentList.clear();
}

void GameObject::AddComponent(Component* component)
{
	componentList.push_back(component);
}
