#pragma once
class Scene
{
public:
	std::vector<GameObject*> objectList;
	EventListener* eventListener;

	Scene();
	~Scene();

	void DrawScene(ShaderProgram& shaderProgram, glm::mat4 projection);
	void AddObject(GameObject* object);
	void DeleteObject(GameObject* object);
	GameObject* FindInScene(std::string name);
	void SpawnObject(Event* event);
	void DestoryObject(Event* event);
};

