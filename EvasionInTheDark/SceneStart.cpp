#include "stdafx.h"
#include "SceneStart.h"
#include "Logo.h"
#include "TitleUi.h"

SceneStart::SceneStart() : Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	logo = AddGo(new Logo("Logo"));
	titleUi = AddGo(new TitleUi("TitleUi"));
	logo->SetOrigin(Origins::MC);
	titleUi->SetOrigin(Origins::MC);

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);

	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/bgm.wav"), true);
	SoundMgr::Instance().SetBgmVolume(2.f);
	Scene::Init();
}

void SceneStart::Release()
{
	Scene::Release();
}

void SceneStart::Enter()
{
	SoundMgr::Instance().PlayBgm("sound/bgm.wav");

	Scene::Enter();
}

void SceneStart::Exit()
{
	Scene::Exit();

}

void SceneStart::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneStart::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

}

void SceneStart::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);

}
