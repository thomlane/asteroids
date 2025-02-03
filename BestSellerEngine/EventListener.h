#pragma once
#include <map>
#include <string>
#include <functional>
#include "Event.h"
#include "EventHandler.h"

class EventListener
{
private:
    std::map<std::string, std::function<void(Event*)>> subscribedEventMap;

public:
    void BroadcastEvent(Event*);
    void SubscribeToEvent(std::string name, std::function<void(Event*)> callback);
    void EventCallback(std::string, Event* event);
};