#pragma once
#include "bsepch.h"
class Transform
{
private:
	glm::mat4 transform;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	glm::mat4 Translate();
	glm::mat4 Rotate();
	glm::mat4 Scale();

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Transform(glm::vec3 position, glm::vec3 rotation);
	Transform(glm::vec3 position);
	Transform();

	glm::vec3 Forward();
	float ForwardAngle();

	glm::vec3 SafeNormalize(glm::vec3& v);
	
	//inline glm::vec3 GetPosition()  const { return this->position;  }
	inline glm::vec3 GetRotation()  const { return this->rotation; }
	inline glm::vec3 GetScale()	    const { return this->scale; }
	inline glm::mat4 GetTransform() const { return this->transform; }

	//inline void SetPosition (const glm::vec3 position) { this->position = position; }
	inline void SetRotation(const glm::vec3 rotation) { this->rotation = rotation; }
	inline void SetScale(const glm::vec3 scale) { this->scale = scale; }

	void Update();
	glm::mat4 GetModelMatrix();
};

