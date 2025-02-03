#include "bsepch.h"
#include "ObjectFactory.h"

glm::vec3 RotateVector(glm::vec3 vector, float angle)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));
	glm::vec3 rotated = glm::vec3(rotationMatrix * glm::vec4(vector, 1.0f));
	return rotated;
}

glm::vec3 RandomDirection(glm::vec3 direction, float angleRange)
{
	float randomAngle = randRange(angleRange);
	glm::vec3 norm = glm::normalize(RotateVector(direction, randomAngle));
	return norm;
}
glm::vec3 SafeNormalize(glm::vec3 vector)
{
	glm::vec3 zero = glm::vec3(0);
	if (vector != zero)
		return glm::normalize(vector);
	return zero;
}

GameManager::GameManager()
	: score (0)
{
	eventListener = new EventListener();

	eventListener->SubscribeToEvent("Collision", std::bind(&GameManager::CollisionCallback, this, std::placeholders::_1));
	eventListener->SubscribeToEvent("GameOver", std::bind(&GameManager::GameOver, this, std::placeholders::_1));
	srand(time(NULL));
}

void GameManager::GameOver(Event* event)
{
	printf(" == You Lost ==\n");
	printf(" == Final Score: %d ==\n", score);
	SpawnGameOver();
}

void GameManager::Update(Scene& scene)
{
	bool stillBigAsteroids = false;
	for (GameObject* object : scene.objectList)
	{
		PhysicsBodyComponent* body = object->FindComponent<PhysicsBodyComponent>();
		if (body == nullptr) continue;
		if (body->categoryMask == BitLevels::BulletMask)
		{
			if (object->lifeTimer > bulletLifeTime)
			{
				eventListener->BroadcastEvent(new ObjectEvent("Destroy", object, DespawnEvent));
				continue;
			}
		}
		else if (body->categoryMask == BitLevels::AsteroidMask)
		{
			if (object->name[0] == 'b') // big asteroid
				stillBigAsteroids = true;
		}

		float windowHalfWidth = 1.0f;
		float windowHalfHeight = 1.0f;
		if (object->transform.position.x > windowHalfWidth || object->transform.position.x < -windowHalfWidth)
			object->transform.position.x *= -1;
		if (object->transform.position.y > windowHalfHeight || object->transform.position.y < -windowHalfHeight)
			object->transform.position.y *= -1;
	}
	if (!stillBigAsteroids)
	{
		int num = rand() % 5 + 1;
		AsteroidGenerator(num);
	}
}

/// <summary>
/// Randomly spawn big asteroids on the edges of the screen and give them a random angle.
/// </summary>
/// <param name="num">The number of large asteroids to spawn.</param>
void GameManager::AsteroidGenerator(int num)
{
	for (int i = 0; i < num; ++i)
	{
		int extremePosition = rand() % 2 * 2 - 1;
		glm::vec3 randStart = rand() % 2 ? glm::vec3(randRange(1), extremePosition,0) : glm::vec3(extremePosition, randRange(1),0);
		glm::vec3 velocity = RandomDirection(-randStart,40) * bigAsteroidSpeed;
		SpawnBigAsteroid(randStart, velocity);
	}
}

void GameManager::CollisionCallback(Event* event)
{
	CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*> (event);
	std::string body1Name = collisionEvent->body1->owner->name;
	std::string body2Name = collisionEvent->body2->owner->name;

	DistributeObject(collisionEvent->body1->owner);
	DistributeObject(collisionEvent->body2->owner);
}

// 

/// <summary>
/// Pass each collided object to the proper collision response function.
/// </summary>
/// <param name="object">The object that collided.</param>
void GameManager::DistributeObject(GameObject* object)
{
	PhysicsBodyComponent* body = object->FindComponent<PhysicsBodyComponent>();
	switch (body->categoryMask)
	{
		case BitLevels::PlayerMask:
			PlayerCollision(object);
			break;
		case BitLevels::BulletMask:
			BulletCollision(object);
			break;
		case BitLevels::AsteroidMask:
			AsteroidCollision(object);
			break;
	}
}

/// <summary>
/// Manage what should happen when the player collides with another object.
/// </summary>
/// <param name="object">The player object that collided.</param>
void GameManager::PlayerCollision(GameObject* object)
{
	eventListener->BroadcastEvent(new ObjectEvent("Destroy", object, DespawnEvent));
	eventListener->BroadcastEvent(new EmptyEvent("GameOver"));
}

/// <summary>
/// Manage what should happen when a bullet collides with another object.
/// </summary>
/// <param name="object">The bullet that collided.</param>
void GameManager::BulletCollision(GameObject* object)
{
	eventListener->BroadcastEvent(new ObjectEvent("Destroy", object, DespawnEvent));
}

/// <summary>
/// Manage what should happen when a asteroid collides with another object.
/// </summary>
/// <param name="object">The asteroid that collided.</param>
void GameManager::AsteroidCollision(GameObject* object)
{
	if (object->name[0] == 'b') // big asteroid
	{
		glm::vec3 parentVelocity = object->FindComponent<PhysicsBodyComponent>()->GetVelocity();
		float step = mediumAsteroidSpawnNum > 1 ? (2 * mediumAsteroidSpread) / (mediumAsteroidSpawnNum - 1) : mediumAsteroidSpread;
		for (int i = 0; i < mediumAsteroidSpawnNum; ++i)
		{
			float angle = -mediumAsteroidSpread + i * step;
			glm::vec3 velocity = mediumAsteroidSpeed * SafeNormalize(RotateVector(parentVelocity, angle));
			SpawnMediumAsteroid(object->transform.position, velocity);
		}
		score += bigAsteroidScore;
	}
	else if (object->name[0] == 'm')
	{
		glm::vec3 parentVelocity = object->FindComponent<PhysicsBodyComponent>()->GetVelocity();
		float step = smallAsteroidSpawnNum > 1 ? (2 * smallAsteroidSpread) / (smallAsteroidSpawnNum - 1) : smallAsteroidSpread;
		for (int i = 0; i < smallAsteroidSpawnNum; ++i)
		{
			float angle = -smallAsteroidSpread + i * step;
			glm::vec3 velocity = smallAsteroidSpeed * SafeNormalize(RotateVector(parentVelocity, angle));
			SpawnSmallAsteroid(object->transform.position, velocity);
		}
		score += mediumAsteroidScore;
	}
	else
	{
		score += smallAsteroidScore;
	}
		eventListener->BroadcastEvent(new ObjectEvent("Destroy", object, DespawnEvent));
}