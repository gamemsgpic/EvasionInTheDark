#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Track.h"
#include "Enemy.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	player = AddGo(new Player("Player"));
	track = AddGo(new Track("Track"));
	enemy = AddGo(new Enemy("Enemy"));
	player->SetOrigin(Origins::MC);
	track->SetOrigin(Origins::MC);
	enemy->SetOrigin(Origins::MC);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);

	SpawnTrack(3);
	Scene::Enter();
}

void SceneGame::Exit()
{
	for (auto track : tracks)
	{
		RemoveGo(track);
		trackPool.Return(track);
	}
	tracks.clear();
	for (auto enemy : enemys)
	{
		RemoveGo(enemy);
		enemyPool.Return(enemy);
	}
	enemys.clear();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	spawnEnemy += dt;
	if (spawnEnemy > spawnDelay)
	{
		SpawnEnemy(1);
		spawnEnemy = 0.f;
	}

	for (auto& enemy : enemys)
	{
		if (enemy->GetPosition().y > FRAMEWORK.GetWindowSizeF().y +
			enemy->GetGlobalBounds().height + 50.f)
		{
			RemoveGo(enemy);
			enemyPool.Return(enemy);
			enemy->SetSoundStop();
		}
	}
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::SpawnTrack(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Track* track = trackPool.Take();
		tracks.push_back(track);

		sf::Vector2f pos = { FRAMEWORK.GetWindowSizeF().x * 0.5f,
			FRAMEWORK.GetWindowSizeF().y * 0.5f };
		if (i == 0)
		{
			track->SetPosition(pos);
		}
		if (i == 1)
		{
			pos.x -= track->GetGlobalBounds().width;
			track->SetPosition(pos);
		}
		if (i == 2)
		{
			pos.x += track->GetGlobalBounds().width;
			track->SetPosition(pos);
		}
		AddGo(track);
	}
}

void SceneGame::SpawnEnemy(int count)
{

	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Take();
		enemys.push_back(enemy);

		int ran = Utils::RandomRange(0, Enemy::TotalTypes - 1);
		Enemy::Types enemyType = (Enemy::Types)ran;
		enemy->SetType(enemyType);

		enemy->SetOrigin(Origins::MC);
		sf::Vector2f pos = { FRAMEWORK.GetWindowSizeF().x * 0.5f,
			0 - enemy->GetGlobalBounds().height - 50.f };

		if (ran == 0)
		{
			pos.x -= track->GetGlobalBounds().width;
			enemy->SetPosition(pos);
		}
		if (ran == 1)
		{
			pos.x += track->GetGlobalBounds().width;
			enemy->SetPosition(pos);
		}
		if (ran == 2)
		{
			enemy->SetPosition(pos);
		}
		AddGo(enemy);
	}
}
