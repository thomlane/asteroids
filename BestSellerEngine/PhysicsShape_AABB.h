#pragma once
class PhysicsShape_Circle;
class Transform;

class PhysicsShape_AABB : public PhysicsShape
{
public:
	PhysicsShape_AABB(glm::vec3 center, float halfWidth, float halfHeight);
	PhysicsShape_AABB(float halfWidth, float halfHeight);
	PhysicsShape_AABB(float half);
	PhysicsShape_AABB(glm::vec3 center);
	PhysicsShape_AABB();
	~PhysicsShape_AABB();

	bool CheckCollisionWith(PhysicsShape* that) const;

	bool CheckCollisionWith(PhysicsShape_AABB* that) const;
	bool CheckCollisionWith(PhysicsShape_Circle* that) const;

	void Update(Transform& transform);
	void Scale(float mult);

	glm::vec3 GetCenter()		const { return center; }
	float GetHalfWidth()	const { return halfWidth; }
	float GetHalfHeight()	const { return halfHeight; }

private:

	glm::vec3 center;
	float halfWidth;
	float halfHeight;
};

