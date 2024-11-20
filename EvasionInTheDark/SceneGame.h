#pragma once
#include "Scene.h"

class Player;
class Track;
class Enemy;
class UiHud;
class aniinstrument;

class SceneGame : public Scene
{
protected:
	Player* player;
	//Track* track;
	Track* tracks[3];
	Enemy* enemy;
	UiHud* uihud;
	aniinstrument* aniInstrument;

	sf::Sound sound;

	std::list<Enemy*> enemys;
	ObjectPool<Enemy> enemyPool;

	//std::list<Track*> tracks;
	//ObjectPool<Track> trackPool;

	float spawnEnemyTime = 0.f;
	float spawnDelay = 5.f;
	float maxDelay = 0.f;

	float upScoreTime = 0.5f;
	float upScoreDelay = 0.5f;

	

	bool hitBoxAct = false;
	bool drumOn = false;
	bool bassOn = false;
	bool castanetsOn = false;
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
	//const std::list<Track*> GetTrackList() { return tracks; }

	bool GetHitBoxAct() { return hitBoxAct; }
	bool GetdrumOn() { return drumOn; }
	bool GetbassOn() { return bassOn; }
	bool GetcastanetsOn() { return castanetsOn; }
	bool GetSpawnDelay() { return spawnDelay; }
	bool GetMaxDelay() { return maxDelay; }

	void SpawnTrack(int count);
	void SpawnEnemy(int count);
	void SpawnSpeedUp() { spawnDelay -= 0.2f; }


};
