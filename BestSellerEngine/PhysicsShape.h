#pragma once

class PhysicsShape_Circle;
class PhysicsShape_AABB;

class PhysicsShape
{
public:
	virtual void Update(Transform& transform) = 0;
	virtual void Scale(float mult) = 0;

	virtual bool CheckCollisionWith(PhysicsShape* that) const = 0;

	virtual bool CheckCollisionWith(PhysicsShape_Circle* other) const = 0;
	virtual bool CheckCollisionWith(PhysicsShape_AABB* other) const = 0;
};