#include "bsepch.h"

PhysicsShape_AABB::PhysicsShape_AABB(glm::vec3 center, float halfWidth, float halfHeight)
	:center(center), halfWidth(halfWidth), halfHeight(halfHeight)
{
}

PhysicsShape_AABB::PhysicsShape_AABB(float halfWidth, float halfHeight)
	:center(glm::vec3(0)), halfWidth(halfWidth), halfHeight(halfHeight)
{
}

PhysicsShape_AABB::PhysicsShape_AABB(float half)
	:center(glm::vec3(0)), halfWidth(half), halfHeight(half)
{
}

PhysicsShape_AABB::PhysicsShape_AABB(glm::vec3 center)
	:center(center), halfWidth(.5f), halfHeight(.5f)
{
}

PhysicsShape_AABB::PhysicsShape_AABB()
	:center(glm::vec3(0)), halfWidth(0.5), halfHeight(0.5)
{
}

PhysicsShape_AABB::~PhysicsShape_AABB()
{
}

bool PhysicsShape_AABB::CheckCollisionWith(PhysicsShape* that) const
{
	if (PhysicsShape_AABB* shape = dynamic_cast<PhysicsShape_AABB*> (that))
		return CheckCollisionWith(shape);
	else if (PhysicsShape_Circle * shape = dynamic_cast<PhysicsShape_Circle*> (that))
		return CheckCollisionWith(shape);
}

bool PhysicsShape_AABB::CheckCollisionWith(PhysicsShape_AABB* that) const
{
	bool collideOnX = (this->GetHalfWidth() + that->GetHalfWidth()) > glm::abs(this->center.x - that->center.x);
	bool collideOnY = (this->GetHalfHeight() + that->GetHalfHeight()) > glm::abs(this->center.y - that->center.y);
	if (collideOnX && collideOnY) return true;
	return false;
}

bool PhysicsShape_AABB::CheckCollisionWith(PhysicsShape_Circle* that) const
{
	float differenceX = glm::abs(this->GetCenter().x - that->GetCenter().x);
	float differenceY = glm::abs(this->GetCenter().y - that->GetCenter().y);
	bool collideOnX = (this->GetHalfWidth() + that->GetRadius()) > differenceX;
	bool collideOnY = (this->GetHalfHeight() + that->GetRadius()) > differenceY;
	if (collideOnX && collideOnY)return true;
	return false;
}

void PhysicsShape_AABB::Update(Transform& transform)
{
	center = transform.position;
}

void PhysicsShape_AABB::Scale(float mult)
{
	halfHeight *= mult;
	halfWidth *= mult;
}
