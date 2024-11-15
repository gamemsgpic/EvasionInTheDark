#include "stdafx.h"
#include "UiHud.h"
#include "SceneGame.h"
#include "Track.h"
#include "Player.h"

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

	track = dynamic_cast<Track*>(SCENE_MGR.GetCurrentScene()->FindGo("Track"));
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	float textSize = 25.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	textScore.setFont(font);
	textScore.setCharacterSize(textSize);
	textScore.setFillColor(sf::Color::White);
	Utils::SetOrigin(textScore, Origins::TR);

	textHighScore.setFont(font);
	textHighScore.setCharacterSize(textSize);
	textHighScore.setFillColor(sf::Color::White);
	Utils::SetOrigin(textHighScore, Origins::TR);

	textLife.setFont(font);
	textLife.setCharacterSize(textSize);
	textLife.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLife, Origins::TR);

	iconLight.setTexture(TEXTURE_MGR.Get("graphics/uilight.png"));
	Utils::SetOrigin(iconLight, Origins::BL);

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	textScore.setPosition(track->GetGlobalBounds().width + 80.f , track->GetGlobalBounds().height / 8);
	textHighScore.setPosition(track->GetGlobalBounds().width + 80.f, track->GetGlobalBounds().height / 8 - (textSize * 2));
	textLife.setPosition(track->GetGlobalBounds().width + 80.f, track->GetGlobalBounds().height / 2 + (textSize * 12));

	iconLight.setPosition(track->GetGlobalBounds().width + 460.f, track->GetGlobalBounds().height / 2);


	SetScore(player->GetScore());
	SetHiScore(player->GetBestScore());
	SetLife(player->GetLife());
}

void UiHud::Update(float dt)
{
	SetScore(player->GetScore());
	SetHiScore(player->GetBestScore());
	SetLife(player->GetLife());
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(textLife);
	window.draw(iconLight);
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
