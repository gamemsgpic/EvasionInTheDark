#pragma once
#include "Scene.h"

class Player;
class Track;
class Enemy;

class SceneGame : public Scene
{
protected:
	Player* player;
	Track* track;
	Enemy* enemy;

	std::list<Enemy*> enemys;
	ObjectPool<Enemy> enemyPool;

	std::list<Track*> tracks;
	ObjectPool<Track> trackPool;

	float spawnEnemy = 0.f;
	float spawnDelay = 5.f;

	int level = 0;
	int bestLevel = 0;
	int levelUp = 0;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init();
	void Release();

	void Enter();
	void Exit();

	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);

	void SpawnTrack(int count);
	void SpawnEnemy(int count);


};
