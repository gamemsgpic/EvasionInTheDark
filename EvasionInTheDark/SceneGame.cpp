#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Track.h"
#include "Enemy.h"
#include "UiHud.h"
#include "aniinstrument.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	player = AddGo(new Player("Player"));
	//track = AddGo(new Track("Track"));
	tracks[0] = AddGo(new Track("Track"));
	tracks[1] = AddGo(new Track("Track"));
	tracks[2] = AddGo(new Track("Track"));
	enemy = AddGo(new Enemy("Enemy"));
	uihud = AddGo(new UiHud("UiHud"));
	aniInstrument = AddGo(new aniinstrument("instrument"));
	player->SetOrigin(Origins::MC);
	//track->SetOrigin(Origins::MC);
	enemy->SetOrigin(Origins::MC);
	aniInstrument->SetOrigin(Origins::MC);
	//enemy->ChangeEnemyDie(false);

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);


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
	//for (auto track : tracks)
	//{
	//	RemoveGo(track);
	//	trackPool.Return(track);
	//}
	//tracks.clear();
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
	if (player->GetEasy() == true)
	{
		maxDelay = 4.f;
	}
	if (player->GetNormal() == true)
	{
		maxDelay = 2.5f;
	}
	if (player->GetExtreme() == true)
	{
		maxDelay = 1.5f;
	}

	spawnEnemyTime += dt;
	if (spawnDelay <= maxDelay)
	{
		spawnDelay = maxDelay;
	}
	if (player->GetSpawnChange() == false && spawnEnemyTime > spawnDelay)
	{

		player->ChangePlayerHit(false);
		SpawnEnemy(Utils::RandomRange(1, 2));
		spawnEnemyTime = 0.f;

	}
	//else if (player->GetSpawnChange() == true && spawnEnemyTime > spawnDelay)
	//{
	//	player->ChangePlayerHit(false);
	//	SpawnEnemy(2);
	//	spawnEnemyTime = 0.f;
	//}

	upScoreTime += dt;
	for (auto& enemy : enemys)
	{

		if (enemy->GetPosition().y > FRAMEWORK.GetWindowSizeF().y +
			enemy->GetGlobalBounds().height + 50.f)
		{
			if (enemy->GetHit() == false && upScoreTime > upScoreDelay)
			{
				if (player->GetPlayerHit() == false)
				{
					player->SetScore();
					player->LevelPointUp();
					SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/scoreup.wav"))->setVolume(0.5f);
					upScoreTime = 0.f;
					uihud->SetScoreOutColor();
				}
			}
			else
			{
				enemy->ChangeHit(false);
			}
			drumOn = false;
			bassOn = false;
			castanetsOn = false;
			enemy->SetSoundVolume();
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
		if (player->GetCurrentTrack() == 0)
		{
			tracks[0]->SetRandomColor();
			tracks[1]->SetWhiteColor();
			tracks[2]->SetWhiteColor();
		}
		else if (player->GetCurrentTrack() == 1)
		{
			tracks[1]->SetRandomColor();
			tracks[0]->SetWhiteColor();
			tracks[2]->SetWhiteColor();
		}
		else if (player->GetCurrentTrack() == 2)
		{
			tracks[2]->SetRandomColor();
			tracks[0]->SetWhiteColor();
			tracks[1]->SetWhiteColor();
		}
	}
	if (player->GetLife() == 0)
	{
		FRAMEWORK.SetTimeScale(0);
		SOUND_MGR.StopAllSfx();
		SOUND_MGR.StopBgm();
		for (auto& enemy : enemys)
		{
			enemy->SetSoundStop();
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		FRAMEWORK.SetTimeScale(1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		hitBoxAct = !hitBoxAct;
	}

	////TEST
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num0))
	//{
	//	SCENE_MGR.ChangeScene(SceneIds::Start);
	//}
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
		if (i == 0)
		{
			tracks[0]->SetPosition({ 740.f, 540.f });
		}
		if (i == 1)
		{
			tracks[1]->SetPosition({ 960.f, 540.f });
		}
		if (i == 2)
		{
			tracks[2]->SetPosition({ 1180.f, 540.f });
		}
	}
	//for (int i = 0; i < count; ++i)
	//{
	//	Track* track = trackPool.Take();
	//	tracks.push_back(track);
	//
	//	sf::Vector2f pos = track->GetPosition();
	//	if (i == 0)
	//	{
	//		pos.x -= track->GetGlobalBounds().width;
	//		track->SetPosition(pos);
	//	}
	//	if (i == 1)
	//	{
	//		track->SetPosition(pos);
	//	}
	//	if (i == 2)
	//	{
	//		pos.x += track->GetGlobalBounds().width;
	//		track->SetPosition(pos);
	//	}
	//	AddGo(track);
	//}
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
			0 - enemy->GetGlobalBounds().height - 300.f };
	
		if (ran == 0)
		{
			//베이스
			pos.x -= 220.f;
			enemy->SetPosition(pos);
			bassOn = true;
			aniInstrument->SetPosBass(Utils::RandomRange(1, 2));
		}
		if (ran == 1)
		{
			//드럼
			enemy->SetPosition(pos);
			drumOn = true;
			aniInstrument->SetPosDrum(Utils::RandomRange(1, 2));
		}
		if (ran == 2)
		{
			
			// 캐스터네츠
			pos.x += 220.f;
			enemy->SetPosition(pos);
			castanetsOn = true;
			aniInstrument->SetPosCastanets(Utils::RandomRange(1, 2));
	
		}
		AddGo(enemy);
	}
}
