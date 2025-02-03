#include "bsepch.h"
#include "EventHandler.h" // Include the actual header file
#include "Event.h"

EventHandler* EventHandler::instance = nullptr;

EventHandler* EventHandler::GetInstance()
{
	if (instance == nullptr) {
		instance = new EventHandler();
	}
	return instance;
}

void EventHandler::EventUpdate()
{
	while (!eventQueue.empty())
	{
		Event* event = eventQueue.front();

		for (auto& subscription : subscriptionMap)
		{
			if (subscription.first == event->GetName())
			{
				subscription.second->EventCallback(subscription.first, event);
			}
		}
		eventQueue.pop();
	}
}

void EventHandler::AddEvent(Event* event)
{
	this->eventQueue.push(event);
}

void EventHandler::AddSubscription(std::string name, EventListener* eventListener)
{
	this->subscriptionMap[name] = eventListener;
}