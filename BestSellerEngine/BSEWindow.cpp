#include "bsepch.h"

BSEWindowHandler* BSEWindowHandler::instance = nullptr;

BSEWindowHandler::BSEWindowHandler() : glfwSuccess(false), pWindow(nullptr), pMonitor(nullptr), shouldClose(false)
{
}

BSEWindowHandler::~BSEWindowHandler()
{
	delete (eventListener);
}

BSEWindowHandler* BSEWindowHandler::GetInstance()
{
	if (instance == nullptr) {
		instance = new BSEWindowHandler();
	}
	return instance;
}

void BSEWindowHandler::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

GLFWwindow* BSEWindowHandler::GetCurrentContext()
{
	return glfwGetCurrentContext();
}

glm::vec2 BSEWindowHandler::WindowSizeWorldCoordinates()
{
	int width, height;
	glfwGetWindowSize(pWindow, &width, &height);
	//glViewport(0, 0, width, height);
	return glm::vec2(width,height);
}

void BSEWindowHandler::Init()
{
	lastframe = 0;
	// set default props if not initialized
	if (Props.Title.empty())
		Props.Title = "Untitled";

	if (Props.Height == 0)
		Props.Height = 1000;

	if (Props.Width == 0)
		Props.Width = 1000;

	// initialize glfw
	if (glfwSuccess)
	{
		std::cout << "GLFW is already initialized!";
		exit(EXIT_FAILURE);
	}
	
	glfwSetErrorCallback(this->GLFWErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwSuccess = true;

	// Initialize OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window
	pWindow = glfwCreateWindow(Props.Width, Props.Height, Props.Title.c_str(), NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(pWindow);

	// Initialize glew (or other gl functions loader)
	GLenum glewError = glewInit();
	if (GLEW_OK != glewError)
	{
		std::cout << "Terminating program. Reason:" << std::endl;
		std::cout << "Error in GLEW: " << glewGetErrorString(glewError) << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
	glfwSetKeyCallback(pWindow, this->GLFWWindowKeyCallback);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	eventListener = new EventListener();
	eventListener->SubscribeToEvent("ExitGame", std::bind(&BSEWindowHandler::CloseWindow, this, std::placeholders::_1));
}

void BSEWindowHandler::Update()
{
	if (!pWindow)
	{
		std::cout << "Window has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	deltaTime = glfwGetTime() - lastframe;
	lastframe = glfwGetTime();

	// this should not be responsibility of Window. Maybe something like a BufferDraw
	glfwGetFramebufferSize(pWindow, &FrameBuffer.Width, &FrameBuffer.Height);
	glViewport(0, 0, FrameBuffer.Width, FrameBuffer.Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	if (glfwWindowShouldClose(pWindow))
		shouldClose = true;
}

void BSEWindowHandler::ShutDown()
{
	if (!pWindow)
	{
		std::cout << "Window can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}
	if(!glfwSuccess)
	{
		std::cout << "GLFW  can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();
}

bool BSEWindowHandler::ShouldClose()
{
	return shouldClose;
}

void BSEWindowHandler::GLFWErrorCallback(int error, const char* description)
{
	std::cout << "Error in GLFW: " << description << std::endl;
}

void BSEWindowHandler::CloseWindow(Event* event)
{
	shouldClose = true;
}

void BSEWindowHandler::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "Window being resized... ";
	std::cout << "Width: " << width << " | Height: " << height << std::endl;
}

void BSEWindowHandler::GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}