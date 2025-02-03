#pragma once
#include "Event.h"

class PhysicsBodyComponent;

class CollisionEvent :
    public Event
{
public:
    CollisionEvent(std::string,PhysicsBodyComponent*, PhysicsBodyComponent*);
    PhysicsBodyComponent* body1;
    PhysicsBodyComponent* body2;
};

