#pragma once
#include <queue>
#include <map>
#include <string>
#include "Event.h"
#include "EventListener.h"
class EventListener;

class EventHandler
{
private:
	std::queue<Event*> eventQueue;
	std::map<std::string, EventListener*> subscriptionMap;

	static EventHandler* instance;

	EventHandler  () {};

public:
	~EventHandler () {};
	static EventHandler* GetInstance();

	void EventUpdate();

	void AddEvent(Event* event);
	void AddSubscription(std::string, EventListener*);
};