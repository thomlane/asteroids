#pragma once
#include "EventListener.h"
class InputManager
{
public:
	static InputManager* GetInstance();
	void InitializeInteraction(GLFWwindow*);
	EventListener eventListener;
	~InputManager() {};
private:
	InputManager() {};
	static InputManager* instance;
	EventListener GetEventListener() const { return eventListener; };
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

