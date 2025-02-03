#include "bsepch.h"
#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return instance;
}

void InputManager::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	EventListener eventListener = InputManager::GetInstance()->GetEventListener();

	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		std::string name;
		switch (key)
		{
			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				name = "MoveForward";
				break;
			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				name = "MoveBack";
				break;

			case GLFW_KEY_Q:
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				name = "RotateCounterClockwise";
				break;

			case GLFW_KEY_E:
			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				name = "RotateClockwise";
				break;

			case GLFW_KEY_SPACE:
				name = "Fire";
				break;

			case GLFW_KEY_ESCAPE:
				name = "ExitGame";
				break;

			default:
				printf("Unrecognized key: %c (%i)\n", key, key);
				break;
		}
		if (!name.empty())
		{
			KeyEvent* event = new KeyEvent(name, key, action, false);
			eventListener.BroadcastEvent(event);
		}
	}
}

void InputManager::InitializeInteraction(GLFWwindow* window)
{
	glfwSetKeyCallback(window, GLFWKeyCallback);
	//glfwSetMouseButtonCallback(window, MouseButton);
	//glfwSetCursorPosCallback(scene.window, MouseMotion);
	//glfwSetScrollCallback(scene.window, Scroll);
}

