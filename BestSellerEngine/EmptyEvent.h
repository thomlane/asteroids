#pragma once
#include "bsepch.h"
class EmptyEvent :
    public Event
{
public:
    EmptyEvent(std::string name) : Event(name) {}
};

