#pragma once

enum BitLevels
{
	PlayerMask = 1 << 0,
	AsteroidMask = 1 << 1,
	BulletMask = 1 << 2
};

const float bigAsteroidScale = .4f;
const float bigAsteroidSpeed = 0.1f;
const float bigAsteroidSpin  = 20.f;
const int   maxBigAsteroids = 5;
const int   bigAsteroidScore = 1;
const std::vector<std::string> bigAsteroidTexturePaths{
	"BigAsteroid1.png",
	"BigAsteroid2.png",
	"BigAsteroid3.png"
};

const float mediumAsteroidScale = 0.2f;
const float mediumAsteroidSpeed = 0.1f;
const float mediumAsteroidSpin = 40.f;
const int   mediumAsteroidSpawnNum = 2;
const float mediumAsteroidSpread = 30.f;
const int   mediumAsteroidScore = 3;
const std::vector<std::string> mediumAsteroidTexturePaths{
	"mediumAsteroid1.png",
	"mediumAsteroid2.png",
	"mediumAsteroid3.png"
};

const float smallAsteroidScale = 0.1f;
const float smallAsteroidSpeed = 0.1f;
const float smallAsteroidSpin = 60.f;
const int   smallAsteroidSpawnNum = 3;
const float smallAsteroidSpread = 30.f;
const int   smallAsteroidScore = 5;
const std::vector<std::string> smallAsteroidTexturePaths{
	"smallAsteroid1.png",
	"smallAsteroid2.png",
	"smallAsteroid3.png"
};

const float bulletScale = 0.1f;
const float bulletSpeed = .8f;
const float bulletLifeTime = 1.5f;
const std::vector<std::string> bulletTexturePaths{
	"bullet_big.png",
	"bullet_small.png"
};

const float playerScale = 0.2f;
const std::vector<std::string> playerTexturePaths{
	"ship_neutral.png",
	"ship_thurst.png"
};

const std::string gameOverPath = "game_over.png";

void SpawnPlayer (glm::vec3 position = glm::vec3(0), float forward = 0);
void SpawnBullet (glm::vec3 position = glm::vec3(0), float forward = 0);
void SpawnBigAsteroid(glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0));
void SpawnMediumAsteroid(glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0));
void SpawnSmallAsteroid(glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0));
void SpawnGameOver();
float randRange(float range);
