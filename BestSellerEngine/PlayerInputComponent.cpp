#include "bsepch.h"
#include "PlayerInputComponent.h"

enum InputFieldEnum {
	MoveForward = 1,
	MoveBackward = 2,
	MoveRight = 4,
	MoveLeft = 8,
	RotateClockwise = 16,
	RotateCounterClockwise = 32,
	Fire = 64
};

PlayerInputComponent::PlayerInputComponent(GameObject* owner)
	: Component(owner)
{
	std::function<void(Event*)> callback = std::bind(&PlayerInputComponent::MovementCallback, this, std::placeholders::_1);
	owner->eventListener->SubscribeToEvent("MoveForward", callback);
	//owner->eventListener->SubscribeToEvent("MoveBack", callback);
	owner->eventListener->SubscribeToEvent("RotateCounterClockwise", callback);
	owner->eventListener->SubscribeToEvent("RotateClockwise", callback);
	owner->eventListener->SubscribeToEvent("Fire", callback);
}

void PlayerInputComponent::MovementCallback(Event* event)
{
	KeyEvent* keyEvent = dynamic_cast<KeyEvent*> (event);
	if (keyEvent->Pressed())
	{
		if      (keyEvent->GetName() == "MoveForward")			  inputField |= MoveForward;
		else if (keyEvent->GetName() == "MoveBack")				  inputField |= MoveBackward;
		else if (keyEvent->GetName() == "RotateCounterClockwise") inputField |= RotateCounterClockwise;
		else if (keyEvent->GetName() == "RotateClockwise")		  inputField |= RotateClockwise;
		else if (keyEvent->GetName() == "Fire")					  inputField |= Fire;
	}
	if (keyEvent->Released())
	{
		if      (keyEvent->GetName() == "MoveForward")            inputField &= ~MoveForward;
		else if (keyEvent->GetName() == "MoveBack")               inputField &= ~MoveBackward;
		else if (keyEvent->GetName() == "RotateCounterClockwise") inputField &= ~RotateCounterClockwise;
		else if (keyEvent->GetName() == "RotateClockwise")        inputField &= ~RotateClockwise;
	}
}

void PlayerInputComponent::Update()
{
	PhysicsBodyComponent* body = owner->FindComponent<PhysicsBodyComponent>();

	glm::vec3 moveDir = glm::vec3(0);
	if (inputField & MoveForward) moveDir = owner->transform.Forward();
	if (inputField & MoveBackward) moveDir = -owner->transform.Forward();
	if (moveDir != glm::vec3(0)) body->ApplyForce(moveDir * playerMoveAcceleration);

	float rotate = 0;
	if (inputField & RotateClockwise) rotate -= 1;
	if (inputField & RotateCounterClockwise) rotate += 1;
	if (rotate != 0)
	{
		float rotateValue = rotate;
		if (playerRotatationalAcceleration == -1)	// turn at full speed or 0
		{
			rotateValue *= playerMaxTurnSpeed;
			body->rotationalVelocity = rotateValue;
		}
		else
		{
			rotateValue *= playerRotatationalAcceleration;
			body->ApplyTorque(rotateValue);
		}
	}
	else
	{
		body->rotationalVelocity = 0;
	}

	
 	if (inputField & Fire)
	{
		inputField &= ~Fire;
		SpawnBullet(owner->transform.position,owner->transform.ForwardAngle());
	}
}
