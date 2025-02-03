#include "bsepch.h"
#include "Scene.h"

Scene::Scene()
{
	eventListener = new EventListener();
	eventListener->SubscribeToEvent("Spawn", std::bind(&Scene::SpawnObject, this, std::placeholders::_1));
	eventListener->SubscribeToEvent("Destroy", std::bind(&Scene::DestoryObject, this, std::placeholders::_1));
}

Scene::~Scene()
{
	delete(eventListener);
}

void Scene::DrawScene(ShaderProgram& shaderProgram, glm::mat4 projection)
{
	for (GameObject* object : objectList)
	{
		object->Update();

		object->FindComponent<RenderComponent>()->texture.Bind(0, "u_Texture", shaderProgram.GetShaderProgram());
		shaderProgram.SetUniform4fv("MVP", 1, GL_FALSE, projection * object->transform.GetModelMatrix());
		object->FindComponent<RenderComponent>()->Draw();
	}
}

void Scene::AddObject(GameObject* object)
{
	std::string name = object->name;
	while (GameObject* temp = FindInScene(name))
	{
		if (temp)
		{
			int number = 1;
			size_t close = name.find(')');
			if (close != -1) // This object is already numbered
			{
				size_t open = name.find('(');
				std::string str_num = name.substr(open + 1, close);
				number = std::stoi(str_num) + 1;
				name.erase(open - 1);
			}
			name += " (" + std::to_string(number) + ")";
			object->name = name;
		}
	}
	objectList.push_back(object);
}

void Scene::DeleteObject(GameObject* object)
{
 	if (object)
	{
		auto it = std::find(objectList.begin(), objectList.end(), object);
		if (it == objectList.end()) // This might happen if one object collides with multiple other objects
		{ 
			return;
		}
		objectList.erase(it);
		delete object;
	}
}

GameObject* Scene::FindInScene(std::string name)
{
	for (GameObject* object : objectList)
	{
		if (object->name == name)
		{
			return object;
		}
	}
	return nullptr;
}

void Scene::SpawnObject(Event* event)
{
	ObjectEvent* objectEvent = dynamic_cast<ObjectEvent*> (event);
	AddObject(objectEvent->object);
}

void Scene::DestoryObject(Event* event)
{
	ObjectEvent* objectEvent = dynamic_cast<ObjectEvent*> (event);
	DeleteObject(objectEvent->object);
}
