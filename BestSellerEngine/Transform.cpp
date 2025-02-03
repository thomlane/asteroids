#include "bsepch.h"
#include "Transform.h"



glm::mat4 Transform::Translate()
{
	return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Transform::Rotate()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
		 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
		 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Transform::Scale()
{
	return glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Transform::Forward()
{
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0., 0., 1.));
	return glm::vec3(rotate * glm::vec4(1.f, 0.f, 0.f, 1.f));
}

float Transform::ForwardAngle()
{
	return rotation.z;
}

glm::vec3 Transform::SafeNormalize(glm::vec3& v)
{
	float lengthSquared = glm::dot(v, v);

	// Check if the length is very close to zero (using an epsilon value)
	if (lengthSquared < glm::epsilon<float>()) {
		// Return a zero vector or any other default value
		return glm::vec3(0.0f);
	}
	else {
		// Normalize the vector as usual
		return glm::normalize(v);
	}
}


/**********************************************************************************************/

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	:position(position), rotation(rotation), scale(scale),
	 translationMatrix(glm::mat4(1)), rotationMatrix(glm::mat4(1)), scaleMatrix(glm::mat4(1)),
	 transform(glm::mat4(1.))
{
	Update();
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation)
	: Transform(position, rotation, glm::vec3(1.))
{

}

Transform::Transform(glm::vec3 position)
	: Transform(position, glm::vec3(0.))
{
}

Transform::Transform()
	: Transform(glm::vec3(0.))
{
}

void Transform::Update() {
	translationMatrix = Translate();
	rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Transform::GetModelMatrix() {
	return translationMatrix * rotationMatrix * scaleMatrix;
}
