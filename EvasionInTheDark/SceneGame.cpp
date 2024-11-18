#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Track.h"
#include "Enemy.h"
#include "UiHud.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	player = AddGo(new Player("Player"));
	track = AddGo(new Track("Track"));
	enemy = AddGo(new Enemy("Enemy"));
	uihud = AddGo(new UiHud("UiHud"));
	player->SetOrigin(Origins::MC);
	track->SetOrigin(Origins::MC);
	enemy->SetOrigin(Origins::MC);
	//enemy->ChangeEnemyDie(false);

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);


	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/bgm.wav"), true);
	SoundMgr::Instance().SetBgmVolume(2.f);
	SoundMgr::Instance().PlayBgm("sound/bgm.wav");
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	

	//enemy->ChangeEnemyDie(false);
	SOUND_MGR.PlayBgm("sound/bgm.wav");
	spawnDelay = 5.f;
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

	spawnEnemyTime += dt;
	if (spawnDelay <= 4.f)
	{
		spawnDelay = 4.f;
	}
	if (spawnEnemyTime > spawnDelay)
	{
		SpawnEnemy(Utils::RandomRange(1, 2));
		spawnEnemyTime = 0.f;
	}

	upScoreTime += dt;
	for (auto& enemy : enemys)
	{
		
		if (enemy->GetPosition().y > FRAMEWORK.GetWindowSizeF().y +
			enemy->GetGlobalBounds().height + 50.f)
		{
			if (enemy->GetHit() == false && upScoreTime > upScoreDelay)
			{
				player->SetScore();
				player->LevelPointUp();
				sound = SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/scoreup.wav"), false);
				sound->setVolume(0.5f);
				upScoreTime = 0.f;
			}
			else
			{
				enemy->ChangeHit(false);
			}
			enemy->SetSoundStop();
			RemoveGo(enemy);
			enemyPool.Return(enemy);
			enemys.remove(enemy);
			break;
		}
	}
	//트랙 색상 바꾸는 것
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) || InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		auto it = tracks.begin();
		int count = 0;
		while (it != tracks.end())
		{
			if (count == player->GetCurrentTrack())
			{
				(*it)->SetRandomColor();
			}
			else
			{
				(*it)->SetColor();

			}
			++count;
			++it;
		}
	}
	if (player->GetLife() == 0)
	{
		FRAMEWORK.SetTimeScale(0);
		SOUND_MGR.StopAllSfx();
		SOUND_MGR.StopBgm();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
		FRAMEWORK.SetTimeScale(1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		hitBoxAct = !hitBoxAct;
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

		sf::Vector2f pos = track->GetPosition();
		if (i == 0)
		{
			pos.x -= track->GetGlobalBounds().width;
			track->SetPosition(pos);
		}
		if (i == 1)
		{
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
		enemy->GravityUp(player->GetLevel());

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
