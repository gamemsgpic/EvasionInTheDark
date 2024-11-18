#include "stdafx.h"
#include "TitleUi.h"

TitleUi::TitleUi(const std::string& name)
{
}

void TitleUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TitleUi::SetRotation(float angle)
{
	rotation = angle;
}

void TitleUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TitleUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
	}
}

void TitleUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TitleUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void TitleUi::Release()
{

}

void TitleUi::Reset()
{
	TEXTURE_MGR.Get(textureId).setSmooth(true);
	gameStart.setTexture(TEXTURE_MGR.Get(textureId));
	gameStart.setScale(1.f, 1.f);
	Utils::SetOrigin(gameStart, Origins::MC);

	gameStart.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.8f);
}

void TitleUi::Update(float dt)
{
	colorChange += dt;

	mousePos = sf::Mouse::getPosition();
	if (gameStart.getGlobalBounds().contains(SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos)))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		if (colorChange > changedelay)
		{
			gameStart.setColor(sf::Color(Utils::RandomColor()));
			colorChange = 0.f;
		}
	}
	else
	{
		gameStart.setColor(sf::Color::White);
	}
}

void TitleUi::Draw(sf::RenderWindow& window)
{
	window.draw(gameStart);
}
