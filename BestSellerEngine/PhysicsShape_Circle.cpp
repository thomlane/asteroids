#include "bsepch.h"

PhysicsShape_Circle::PhysicsShape_Circle(glm::vec3 center, float radius)
    : center(center), radius(radius)
{
}

PhysicsShape_Circle::PhysicsShape_Circle(float radius)
    : center(0.0f), radius(radius)
{
}

PhysicsShape_Circle::PhysicsShape_Circle(glm::vec3 center)
    : center(center), radius(.5f)
{
}

PhysicsShape_Circle::PhysicsShape_Circle()
    : center(0), radius(.5f)
{}

PhysicsShape_Circle::~PhysicsShape_Circle()
{
}

void PhysicsShape_Circle::Update(Transform& transform)
{
    center = transform.position;
}

void PhysicsShape_Circle::Scale(float mult)
{
    radius *= mult;
}

bool PhysicsShape_Circle::CheckCollisionWith(PhysicsShape* that) const
{
    if (PhysicsShape_AABB* shape = dynamic_cast<PhysicsShape_AABB*> (that))
        return CheckCollisionWith(shape);
    else if (PhysicsShape_Circle* shape = dynamic_cast<PhysicsShape_Circle*> (that))
        return CheckCollisionWith(shape);
}

bool PhysicsShape_Circle::CheckCollisionWith (PhysicsShape_Circle* that) const
{
    double combinedRadius = this->GetRadius() + that->GetRadius();
    double distanceBetween = glm::distance(this->GetCenter(), that->GetCenter());
    if (combinedRadius > distanceBetween) return true;
    return false;
}

bool PhysicsShape_Circle::CheckCollisionWith(PhysicsShape_AABB* that) const
{
    float differenceX = glm::abs(this->GetCenter().x - that->GetCenter().x);
    float differenceY = glm::abs(this->GetCenter().y - that->GetCenter().y);
    float collisionDistanceX = this->GetRadius() + that->GetHalfWidth();
    float collisionDistanceY = this->GetRadius() + that->GetHalfHeight();
    bool collideOnX = collisionDistanceX > differenceX;
    bool collideOnY = collisionDistanceY > differenceY;
    if (collideOnX && collideOnY) return true;
    return false;
}
