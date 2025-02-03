#pragma once

#define GLFW_INCLUDE_NONE
#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

#include "BSEWindow.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Transform.h"
#include "Texture.h"
#include "GameObject.h"
#include "Geometry.h"
#include "GeoFactory.h"

#include "Event.h"
#include "KeyEvent.h"
#include "CollisionEvent.h"
#include "ObjectEvent.h"
#include "EmptyEvent.h"
#include "EventHandler.h"
#include "EventListener.h"


#include "PhysicsBodyComponent.h"
#include "PhysicsShape.h"
#include "PhysicsShape_AABB.h"
#include "PhysicsShape_Circle.h"
#include "PhysicsManager.h"

#include "Component.h"
#include "PhysicsBodyComponent.h"
#include "RenderComponent.h"
#include "PlayerInputComponent.h"
#include "StaticInputComponent.h"

#include "InputManager.h"
#include "Scene.h"
#include "GameManager.h"
#include "ObjectFactory.h"
