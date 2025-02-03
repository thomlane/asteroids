#include "bsepch.h"
#include "PhysicsManager.h"

#pragma region ErrorChecks
static void getGLError()
{
    GLenum err = glGetError();
    if (GLEW_OK != err)
    {
        std::cout << "Terminating program. Reason:" << std::endl;
        std::cout << "Error in GLEW: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

static void getShaderCompilationError(GLuint shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
#pragma endregion

int main()
{
#pragma region Initialization    
    BSEWindowHandler* window = BSEWindowHandler::GetInstance();
    window->Props.Title = "Wyld Window";
    window->Init();

    InputManager* inputManager = InputManager::GetInstance();
    inputManager->InitializeInteraction(window->GetCurrentContext());

    EventHandler* eventHandler = EventHandler::GetInstance();
    EventListener eventListener;


    PhysicsManager* physicsManager = PhysicsManager::GetInstance();
    physicsManager->Initialize();

    GameManager gameManager;

    Scene scene;
#pragma endregion

#pragma region shader setup
    Shader vertShader(GL_VERTEX_SHADER, "tex.vert");
    Shader fragShader(GL_FRAGMENT_SHADER, "tex.frag");
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->AddShader(GL_VERTEX_SHADER, "tex.vert");
    shaderProgram->AddShader(GL_FRAGMENT_SHADER, "tex.frag");
    shaderProgram->AttachShaders();
    getGLError();
#pragma endregion

#pragma region Start
    SpawnPlayer(glm::vec3(0,0,0), 90);
    getGLError();
#pragma endregion

#pragma region Main Loop
    //== Main Loop ==//
    float ratio;
    glm::mat4 projection;
    while (!window->ShouldClose())
    {
        window->Update();
        eventHandler->EventUpdate();
        physicsManager->Update();
        gameManager.Update(scene);

        ratio = window->FrameBuffer.Width / (float)window->FrameBuffer.Height;
        projection = glm::ortho(-ratio, ratio, -ratio, ratio, -ratio, ratio);

        shaderProgram->Use();

        scene.DrawScene(*shaderProgram, projection);

        shaderProgram->Unuse();

        window->SwapBuffers();
    }
#pragma endregion

    delete(shaderProgram);
    window->ShutDown();
    exit(EXIT_SUCCESS);
}