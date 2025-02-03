#pragma once

class PhysicsShape;

class PhysicsBodyComponent :
    public Component
{
public:
	PhysicsShape* shape;

	glm::vec3 velocity;				// units per second
	float rotationalVelocity;	// degrees per second in each axis (order: xyz)

	float maxSpeed;					// units per second   (value of -1 means no max)
	float maxTurnSpeed;				// degrees per second (value of -1 means no max)

	float drag;						// units per second in each direction
	float rotationalDrag;			// degrees per second in each axis
	
	float mass;
	float inverseMass;				// Avoids division operation

	void ApplyDrag(double deltaTime);
	void ApplySpeedLimit();

	int collisionMask;
	int categoryMask;
	void Update();
	inline ComponentType GetType() override { return ComponentType::PhysicsBody; }
	void ScaleShape(float mult);

	inline PhysicsShape* GetShape() { return this->shape; }
	inline glm::vec3 GetVelocity() { return this->velocity; }
	inline void ApplyForce (glm::vec3 force)  { velocity += force * inverseMass; }
	inline void ApplyTorque(float torque) { rotationalVelocity += torque * inverseMass; };

	PhysicsBodyComponent(GameObject* owner, PhysicsShape* shape, int categoryMask, int collisionMask,
		glm::vec3 velocity = glm::vec3(0), float maxSpeed = -1, float drag = 0,
		float rotationalVelocity = 0, float maxTurnSpeed = -1, float rotationalDrag = 0,
		float mass = 1.f)
		: Component(owner),shape(shape), categoryMask(categoryMask), collisionMask(collisionMask),
		velocity(velocity), maxSpeed(maxSpeed), drag(drag),
		rotationalVelocity(rotationalVelocity), maxTurnSpeed(maxTurnSpeed), rotationalDrag(rotationalDrag),
		mass(mass), inverseMass(1 / mass)
	{}
	~PhysicsBodyComponent();
};
