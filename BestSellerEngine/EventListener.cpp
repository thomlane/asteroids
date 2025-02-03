#include "bsepch.h"
#include "EventListener.h"
#include "EventHandler.h"

void EventListener::BroadcastEvent(Event* event)
{
	EventHandler* instance = EventHandler::GetInstance();
	instance->AddEvent(event);
}

void EventListener::SubscribeToEvent(std::string name, std::function<void(Event*)> callback)
{
	subscribedEventMap[name] = callback;
	EventHandler::GetInstance()->AddSubscription(name,this);
}

void EventListener::EventCallback(std::string name,Event* event)
{
	auto callbackFunction = subscribedEventMap.find(name);
	if (callbackFunction != subscribedEventMap.end()) {
		callbackFunction->second(event);
	}
}

