#include "stdafx.h"
#include "TutorialScene.h"
#include "TutoUi.h"

TutorialScene::TutorialScene() : Scene(SceneIds::Tuto)
{
}

void TutorialScene::Init()
{
	tutoUi = AddGo(new TutoUi("TutoUi"));

	tutoUi->SetOrigin(Origins::MC);

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f);

	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/bgm.wav"), true);
	SoundMgr::Instance().SetBgmVolume(2.f);
	Scene::Init();
}

void TutorialScene::Release()
{
	Scene::Release();
}

void TutorialScene::Enter()
{
	Scene::Enter();
}

void TutorialScene::Exit()
{
	Scene::Exit();
}

void TutorialScene::Update(float dt)
{
	Scene::Update(dt);
}

void TutorialScene::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void TutorialScene::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}
