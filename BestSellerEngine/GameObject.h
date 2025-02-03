#pragma once
#include "PlayerInputComponent.h"
class PhysicsBodyComponent;
class RenderComponent;
class Geometry;
class EventListener;

class GameObject
{
	std::vector<Component*> componentList;
public:
	std::string name;
	Transform transform;
	EventListener* eventListener;
	double lifeTimer;

	void Update();
	void Scale(float mult);

	GameObject(std::string name, glm::vec3 position, float rotation);
	GameObject(std::string name, glm::vec3 position);
	GameObject(std::string name);
	~GameObject();
	
	void AddComponent(Component* component);

	template <class T>
	T* FindComponent() {
		for (auto it = componentList.begin(); it != componentList.end(); ++it) {
			T* component = dynamic_cast<T*>(*it);
			if (component != nullptr) {
				return component;
			}
		}
		return nullptr;
	}
};
