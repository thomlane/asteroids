#include "bsepch.h"


PhysicsManager* PhysicsManager::instance = nullptr;
class GameObject;

bool PhysicsManager::Colliding(PhysicsBodyComponent* body1, PhysicsBodyComponent* body2) const
{
	PhysicsShape* shape1 = body1->GetShape();
	PhysicsShape* shape2 = body2->GetShape();
	return shape1->CheckCollisionWith(shape2);
}

bool PhysicsManager::CheckMasks(PhysicsBodyComponent* body1, PhysicsBodyComponent* body2) const
{
	return body1->categoryMask & body2->collisionMask;
}

void PhysicsManager::EvaluateCollisions()
{
	for (size_t first = 0; first < physicsBodies.size(); first++)
	{
		for (size_t second = first+1; second < physicsBodies.size(); second++)
		{
			assert(first != second);
			if (CheckMasks(physicsBodies[first], physicsBodies[second]) &&
				Colliding(physicsBodies[first], physicsBodies[second]))
			{
				CollisionEvent* event = new CollisionEvent("Collision",physicsBodies[first], physicsBodies[second]);
				eventListener.BroadcastEvent(event);
			}
		}
	}
}

void PhysicsManager::Update()
{
	EvaluateCollisions();
}

PhysicsManager* PhysicsManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new PhysicsManager();
	}
	return instance;
}

PhysicsBodyComponent* PhysicsManager::BuildBody(
	GameObject* owner, PhysicsShape* shape, int categoryMask, int collisionMask,
	glm::vec3 position, float rotation,
	glm::vec3 velocity, float maxSpeed, float drag,
	float rotationalVelocity, float maxTurnSpeed, float rotationalDrag,
	float mass
)
{
	PhysicsBodyComponent* body = new PhysicsBodyComponent
	(
		owner, shape, categoryMask, collisionMask,
		velocity, maxSpeed, drag,
		rotationalVelocity, maxTurnSpeed, rotationalDrag,
		mass
	);
	physicsBodies.push_back(body);
	return body;
}

void PhysicsManager::DestroyPhysicsBody(PhysicsBodyComponent* body)
{
	if (body)
	{
		auto it = std::find(physicsBodies.begin(), physicsBodies.end(), body);
		physicsBodies.erase(it);
	}
}

void PhysicsManager::Initialize()
{
	//eventListener.SubscribeToEvent("Collision", std::bind(&PhysicsManager::CollisionCallback, this, std::placeholders::_1));
}


void PhysicsManager::CollisionCallback(Event* event)
{
}