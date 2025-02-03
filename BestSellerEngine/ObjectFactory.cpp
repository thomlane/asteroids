#include "bsepch.h"

void SpawnPlayer(glm::vec3 position, float forward)
{
	GameObject* player = new GameObject("player", position, forward);
	auto input = new PlayerInputComponent(player);
	player->AddComponent(
		PhysicsManager::GetInstance()->BuildBody(
			player, new PhysicsShape_AABB(position), PlayerMask, AsteroidMask,
			position, player->transform.ForwardAngle(),
			glm::vec3(0), input->playerMaxSpeed, input->playerDrag,
			0, input->playerMaxTurnSpeed, input->playerRotationalDrag
		)
	);
	player->AddComponent(new RenderComponent(player, BuildSquare() , "ship_neutral.png"));
	player->AddComponent(new PlayerInputComponent(player));
	player->Scale(playerScale);
	player->FindComponent<PhysicsBodyComponent>()->ScaleShape(.48);
	ObjectEvent* event = new ObjectEvent("Spawn", player, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

void SpawnBullet(glm::vec3 position, float forward)
{
	GameObject* bullet = new GameObject("bullet", position, forward);
	PhysicsBodyComponent* body = PhysicsManager::GetInstance()->BuildBody(
		bullet, new PhysicsShape_Circle(position), BulletMask, AsteroidMask,
		position,0, bulletSpeed * bullet->transform.Forward()
	);
	bullet->AddComponent(body);
	int randomTextureIndex = rand() % bulletTexturePaths.size();
	bullet->AddComponent(new RenderComponent(bullet, BuildSquare(), bulletTexturePaths[randomTextureIndex]));
	bullet->Scale(bulletScale);
	bullet->FindComponent<PhysicsBodyComponent>()->ScaleShape(.4);
	bullet->transform.position = position;
	ObjectEvent* event = new ObjectEvent("Spawn", bullet, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

void SpawnBigAsteroid(glm::vec3 position, glm::vec3 velocity)
{
	GameObject* asteroid = new GameObject("bigAsteroid",position);
	float spin = randRange(bigAsteroidSpin);
	PhysicsBodyComponent* body = PhysicsManager::GetInstance()->BuildBody(
			asteroid, new PhysicsShape_Circle(asteroid->transform.position), AsteroidMask, BulletMask | PlayerMask,
			position,0, velocity, -1.0f, 0, spin
	);
	asteroid->AddComponent(body);
	int randomTextureIndex = rand() % bigAsteroidTexturePaths.size();
	asteroid->AddComponent(new RenderComponent(asteroid, BuildSquare(), bigAsteroidTexturePaths[randomTextureIndex]));
	asteroid->Scale(bigAsteroidScale);
	asteroid->FindComponent<PhysicsBodyComponent>()->ScaleShape(.6);
	ObjectEvent* event = new ObjectEvent("Spawn", asteroid, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

void SpawnMediumAsteroid(glm::vec3 position, glm::vec3 velocity)
{
	GameObject* asteroid = new GameObject("mediumAsteroid", position);
	float spin = randRange(mediumAsteroidSpin);
	PhysicsBodyComponent* body = PhysicsManager::GetInstance()->BuildBody(
		asteroid, new PhysicsShape_Circle(asteroid->transform.position), AsteroidMask, BulletMask | PlayerMask,
		position, 0, velocity, -1.0f, 0, spin
	);
	asteroid->AddComponent(body);
	asteroid->Scale(mediumAsteroidScale);
	body->ScaleShape(.6);
	int randomTextureIndex = rand() % mediumAsteroidTexturePaths.size();
	asteroid->AddComponent(new RenderComponent(asteroid, BuildSquare(), mediumAsteroidTexturePaths[randomTextureIndex]));
	ObjectEvent* event = new ObjectEvent("Spawn", asteroid, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

void SpawnSmallAsteroid(glm::vec3 position, glm::vec3 velocity)
{
	GameObject* asteroid = new GameObject("smallAsteroid", position);
	float spin = randRange(smallAsteroidSpin);
	asteroid->AddComponent(
		PhysicsManager::GetInstance()->BuildBody(
			asteroid, new PhysicsShape_Circle(asteroid->transform.position), AsteroidMask, BulletMask | PlayerMask,
			position, 0, velocity, -1.f, 0, spin
		)
	);
	int randomTextureIndex = rand() % smallAsteroidTexturePaths.size();
	asteroid->AddComponent(new RenderComponent(asteroid, BuildSquare(), smallAsteroidTexturePaths[randomTextureIndex]));
	asteroid->Scale(smallAsteroidScale);
	asteroid->FindComponent<PhysicsBodyComponent>()->ScaleShape(.6);
	ObjectEvent* event = new ObjectEvent("Spawn", asteroid, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

void SpawnGameOver()
{
	GameObject* gameover = new GameObject("gameover");
	gameover->AddComponent(new RenderComponent(gameover, BuildSquare(), gameOverPath));
	ObjectEvent* event = new ObjectEvent("Spawn", gameover, SpawnEvent);
	EventListener eventListener;
	eventListener.BroadcastEvent(event);
}

float randRange(float range)
{
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 * range))) - range;
}

