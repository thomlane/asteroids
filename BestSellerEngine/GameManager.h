#pragma once
class GameManager
{
public:
	EventListener* eventListener;

	GameManager();
	~GameManager() { delete(eventListener); }

	void GameOver(Event* event);
	void Update(Scene& scene);

	void AsteroidGenerator(int num);

	void CollisionCallback(Event* event);
	void DistributeObject(GameObject* object);
	void PlayerCollision(GameObject* object);
	void BulletCollision(GameObject* object);
	void AsteroidCollision(GameObject* object);

	int score;
};

