#pragma once
#include "bsepch.h"

const enum EventType {
	SpawnEvent,
	DespawnEvent
};

class ObjectEvent :
	public Event
{
public:
	ObjectEvent(std::string name, GameObject* object, EventType type)
		: Event(name), object(object), type(type) {}
	GameObject* object;
	EventType type;
};