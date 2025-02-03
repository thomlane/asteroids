#pragma once
#include "Component.h"
class GameObject;
class Event;

class PlayerInputComponent :
    public Component
{
public:

	PlayerInputComponent(GameObject* owner);

	inline ComponentType GetType() override { return ComponentType::Input; }

	void MovementCallback(Event* event);
	void Update();

	int inputField = 0;

	float playerMoveAcceleration = .005f;
	const float playerMaxSpeed = .4f;
	const float playerDrag = 0.1f;

	//float playerRotatationalAcceleration = .8f;
	float playerRotatationalAcceleration = -1;
	const float playerMaxTurnSpeed = 180.f;
	const float playerRotationalDrag = 50.f;
};

