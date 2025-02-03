#pragma once

struct GLFWwindow;
struct GLFWMonitor;
class EventListener;
class Event;

struct WindowProps
{
	int Width = 0;
	int Height = 0;
	std::string Title;
};

struct FrameBufferProps
{
	int Width = 0;
	int Height = 0;
};

class BSEWindowHandler
{
public:
	~BSEWindowHandler();

	WindowProps Props;
	FrameBufferProps FrameBuffer;

	double deltaTime;

	
	void Init();
	void Update();
	void ShutDown();
	bool ShouldClose();

	static BSEWindowHandler* GetInstance();
	void SwapBuffers();
	GLFWwindow* GetCurrentContext();
	glm::vec2 WindowSizeWorldCoordinates();

private:
	BSEWindowHandler();
	double lastframe;

	static BSEWindowHandler* instance; 
	EventListener* eventListener;

	// window pointers
	GLFWwindow* pWindow;
	GLFWMonitor* pMonitor;
	
	// glfw setup
	bool glfwSuccess;

	// properties
	bool shouldClose;
	void CloseWindow(Event* event);


	// member functions
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		//std::cout << "OpenGL Debug: " << message << std::endl;
	}
};