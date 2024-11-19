#include "stdafx.h"
#include "TitleUi.h"
#include "Player.h"

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

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	player->SetNormal(true);
	normal.setColor(sf::Color(Utils::RandomColor()));
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

	easy.setTexture(TEXTURE_MGR.Get("graphics/easy.png"));
	easy.setScale(0.5f, 0.5f);
	Utils::SetOrigin(easy, Origins::MC);

	normal.setTexture(TEXTURE_MGR.Get("graphics/normal.png"));
	normal.setScale(0.5f, 0.5f);
	Utils::SetOrigin(normal, Origins::MC);

	extreme.setTexture(TEXTURE_MGR.Get("graphics/extreme.png"));
	extreme.setScale(0.5f, 0.5f);
	Utils::SetOrigin(extreme, Origins::MC);

	gameStart.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.85f);
	easy.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.4f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);
	normal.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);
	extreme.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.6f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);
}

void TitleUi::Update(float dt)
{
	colorChange += dt;

	mousePos = InputMgr::GetMousePosition();
	sf::Vector2f pos = SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos);
	if (gameStart.getGlobalBounds().contains(pos))
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

	if (easy.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(true);
			player->SetNormal(false);
			player->SetExtreme(false);
			easy.setColor(sf::Color(Utils::RandomColor()));
			normal.setColor(sf::Color::White);
			extreme.setColor(sf::Color::White);
		}
	}
	if (normal.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(false);
			player->SetNormal(true);
			player->SetExtreme(false);
			normal.setColor(sf::Color(Utils::RandomColor()));
			easy.setColor(sf::Color::White);
			extreme.setColor(sf::Color::White);
		}
	}
	if (extreme.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(false);
			player->SetNormal(false);
			player->SetExtreme(true);
			extreme.setColor(sf::Color(Utils::RandomColor()));
			easy.setColor(sf::Color::White);
			normal.setColor(sf::Color::White);
		}
	}
}

void TitleUi::Draw(sf::RenderWindow& window)
{
	window.draw(gameStart);
	window.draw(easy);
	window.draw(normal);
	window.draw(extreme);
}
