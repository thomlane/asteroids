#include "bsepch.h"
#include "PhysicsBodyComponent.h"

class GameObject;

void PhysicsBodyComponent::Update()
{
	float deltaTime = BSEWindowHandler::GetInstance()->deltaTime;

	if (drag != 0 || rotationalDrag != 0) ApplyDrag(deltaTime);		// If this body uses drag effects, apply them
	ApplySpeedLimit();
	owner->transform.position += velocity * deltaTime;
	owner->transform.rotation.z += rotationalVelocity * deltaTime;
	shape->Update(owner->transform);
}

void PhysicsBodyComponent::ApplySpeedLimit()
{
	if (maxSpeed != -1 && velocity != glm::vec3(0))
	{
		float velocityMag = glm::length(velocity);
		if (velocityMag > maxSpeed)
		{
			glm::vec3 velocityNorm = glm::normalize(velocity);
			velocity = velocityNorm * maxSpeed;
		}
	}
	if (maxTurnSpeed != -1 && rotationalVelocity != 0)
	{
		float rotationalMag = glm::abs(rotationalVelocity);
		if (rotationalMag > maxTurnSpeed)
		{
			int sign = std::signbit(rotationalVelocity) ? -1 : 1;
			rotationalVelocity = (sign * maxTurnSpeed);
		}
	}
}

void PhysicsBodyComponent::ApplyDrag(double deltaTime)
{
	if (drag != 0 && velocity != glm::vec3(0))
	{
		glm::vec3 normalized = glm::normalize(velocity);
		float magnitude = glm::length(velocity);
		float newSpeed = std::max(0., magnitude - (drag*deltaTime));
		velocity = normalized * newSpeed;
	}
	if (rotationalDrag != 0 && rotationalVelocity != 0)
	{
		float magnitude = glm::abs(rotationalVelocity);
		int sign = std::signbit(rotationalVelocity) ? -1 : 1;
		float newTurnSpeed = std::max(0., magnitude - (rotationalDrag * deltaTime));
		rotationalVelocity = sign * newTurnSpeed;
	}
}

void PhysicsBodyComponent::ScaleShape(float mult)
{
	shape->Scale(mult);
}

PhysicsBodyComponent::~PhysicsBodyComponent()
{
	PhysicsManager* physicsManager = PhysicsManager::GetInstance();
	physicsManager->DestroyPhysicsBody(this);
}
