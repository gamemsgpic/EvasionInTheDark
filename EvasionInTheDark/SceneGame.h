#pragma once
#include "Scene.h"

class Player;
class Track;
class Enemy;
class UiHud;

class SceneGame : public Scene
{
protected:
	Player* player;
	Track* track;
	Enemy* enemy;
	UiHud* uihud;

	std::list<Enemy*> enemys;
	ObjectPool<Enemy> enemyPool;

	std::list<Track*> tracks;
	ObjectPool<Track> trackPool;

	float spawnEnemyTime = 0.f;
	float spawnDelay = 5.f;

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

	const std::list<Enemy*> GetEnemyList() { return enemys; }
	const std::list<Track*> GetTrackList() { return tracks; }

	void SpawnTrack(int count);
	void SpawnEnemy(int count);
	void SpawnSpeedUp() { spawnDelay -= 0.2f; }


};
