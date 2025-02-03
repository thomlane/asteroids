#pragma once
#include "Component.h"
class StaticInputComponent :
    public Component
{
public:
    void Update() {};
    ComponentType GetType() override { return ComponentType::Input; };

    StaticInputComponent(GameObject* owner) : Component(owner) {}

};

