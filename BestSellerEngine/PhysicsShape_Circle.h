#pragma once
class PhysicsShape_AABB;
class Transform;

class PhysicsShape_Circle :
    public PhysicsShape
{
public:
	PhysicsShape_Circle(glm::vec3 center, float radius);
	PhysicsShape_Circle(float radius);
	PhysicsShape_Circle(glm::vec3 center);
	PhysicsShape_Circle();
	~PhysicsShape_Circle();

	void Update(Transform& transform);
	void Scale(float mult);

	bool CheckCollisionWith(PhysicsShape* that) const;

	bool CheckCollisionWith(PhysicsShape_Circle* that) const;
	bool CheckCollisionWith(PhysicsShape_AABB* that) const;

	glm::vec3 GetCenter() const { return center; }
	float GetRadius() const { return radius; }

private:
	glm::vec3 center;
	float radius;
};

