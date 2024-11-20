#include "stdafx.h"
#include "UiHud.h"
#include "SceneGame.h"
#include "Player.h"
//#include "Track.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	//track = dynamic_cast<Track*>(SCENE_MGR.GetCurrentScene()->FindGo("Track"));
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	float textSize = 30.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	textScore.setFont(font);
	textScore.setLetterSpacing(0.2);
	textScore.setCharacterSize(textSize);
	textScore.setFillColor(sf::Color::White);
	textScore.setOutlineColor(sf::Color(Utils::RandomColor()));
	textScore.setOutlineThickness(2);
	Utils::SetOrigin(textScore, Origins::TR);

	textHighScore.setFont(font);
	textHighScore.setLetterSpacing(0.2);
	textHighScore.setCharacterSize(textSize);
	textHighScore.setFillColor(sf::Color::White);
	Utils::SetOrigin(textHighScore, Origins::TR);

	textLife.setFont(font);
	textLife.setLetterSpacing(0.2);
	textLife.setCharacterSize(textSize);
	textLife.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLife, Origins::TR);

	textgameOver.setFont(font);
	textgameOver.setCharacterSize(textSize * 2);
	textgameOver.setFillColor(sf::Color::White);
	textgameOver.setOutlineThickness(2);
	textgameOver.setOutlineColor(sf::Color::Black);
	Utils::SetOrigin(textLife, Origins::MC);

	blindView.setSize(sf::Vector2f{ 2000,1200 });
	blindView.setFillColor(sf::Color::Black);
	Utils::SetOrigin(blindView, Origins::MC);

	iconLight.setTexture(TEXTURE_MGR.Get("graphics/uilightdark.png"));
	iconLight.setTextureRect(sf::IntRect(0, 0, 64, 82));
	iconLight.setScale(0.9f, 0.9f);
	Utils::SetOrigin(iconLight, Origins::BL);

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	textScore.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f - 220.f
		- 220.f * 0.6f, 1080.f / 8 + (textSize * 3));
	textHighScore.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f - 220.f
		- 220.f * 0.6f, 1080.f / 8);
	textLife.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f - 220.f
		- 220.f * 0.6f, 1080.f / 2 + (textSize * 14));
	textgameOver.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f - 175.f,
		FRAMEWORK.GetWindowSizeF().y * 0.5f - 100.f);
	blindView.setPosition(1920 * 0.5f, 1080 * 0.5f);
	
	

	iconLight.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.68f, 1080.f / 2);


	SetScore(player->GetScore());
	SetHiScore(player->GetBestScore());
	SetLife(player->GetLife());
	SetGameOver();
}

void UiHud::Update(float dt)
{
	SetScore(player->GetScore());
	SetHiScore(player->GetBestScore());
	SetLife(player->GetLife());

	if (InputMgr::GetKeyDown(sf::Keyboard::V))
	{
		light = !light;
		if (light == true)
		{
			iconLight.setTextureRect(sf::IntRect(0, 0, 64, 82));
		}
		else
		{
			iconLight.setTextureRect(sf::IntRect(64, 0, 64, 82));
		}
	}
	//if (player->GetLife() == 2)
	//{
	//	textLife.setColor(sf::Color(255,255,225,155));
	//}
	//else if (player->GetLife() == 1)
	//{
	//	textLife.setColor(sf::Color(255, 255, 225, 55));
	//}

}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(textLife);
	if (light == false)
	{
		window.draw(blindView);
	}
	window.draw(iconLight);
	if (player->GetLife() == 0)
	{
		window.draw(textgameOver);
	}
	
}

void UiHud::SetScore(int s)
{
	textScore.setString("SCORE: " + std::to_string(s));
	Utils::SetOrigin(textScore, Origins::TR);
}

void UiHud::SetHiScore(int s)
{
	textHighScore.setString("HI SCORE: " + std::to_string(s));
	Utils::SetOrigin(textHighScore, Origins::TR);
}

void UiHud::SetLife(int current)
{
	textLife.setString("Life: " + std::to_string(current));
	Utils::SetOrigin(textLife, Origins::TR);
}

void UiHud::SetGameOver()
{
	textgameOver.setString("Game Over");
	Utils::SetOrigin(textLife, Origins::TR);
}
