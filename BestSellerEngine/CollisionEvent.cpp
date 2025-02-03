#include "bsepch.h"
#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(std::string name, PhysicsBodyComponent* body1, PhysicsBodyComponent* body2)
	: Event(name), body1(body1), body2(body2)
{}