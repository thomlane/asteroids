#pragma once

class PhysicsManager
{
private:
	static PhysicsManager* instance;
	std::vector<PhysicsBodyComponent*> physicsBodies;

	PhysicsManager() {}
	bool Colliding (PhysicsBodyComponent*, PhysicsBodyComponent*) const;
	bool CheckMasks(PhysicsBodyComponent* body1, PhysicsBodyComponent* body2) const;
	void EvaluateCollisions();

public:
	EventListener eventListener;

	~PhysicsManager() {}
	void Update();
	static PhysicsManager* GetInstance();
	PhysicsBodyComponent* BuildBody(GameObject* owner, PhysicsShape* shape,
		int categoryMask = 0, int collisionMask = 0, 
		glm::vec3 position = glm::vec3(0), float rotation = 0,
		glm::vec3 velocity = glm::vec3(0), float maxSpeed = -1, float drag = 0,
		float rotationalVelocity = 0, float maxTurnSpeed = -1, float rotationalDrag = 0,
		float mass = 1.f);
	void DestroyPhysicsBody(PhysicsBodyComponent* body);
	void Initialize();

	void CollisionCallback(Event* event);

};

