#include "stdafx.h"
#include "TutoUi.h"

TutoUi::TutoUi(const std::string& name)
	: GameObject(name)
{
}

void TutoUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void TutoUi::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void TutoUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void TutoUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void TutoUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void TutoUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void TutoUi::Release()
{
}

void TutoUi::Reset()
{
	float textSize = 30.f;
	float accentTextSize = 33.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	text1.setFont(font);
	text1.setLetterSpacing(0.2);
	text1.setCharacterSize(textSize);
	text1.setFillColor(sf::Color::White);
	text1.setOutlineColor(sf::Color::Black);
	text1.setOutlineThickness(3);
	Utils::SetOrigin(text1, Origins::MC);

	text2.setFont(font);
	text2.setLetterSpacing(0.2);
	text2.setCharacterSize(accentTextSize);
	text2.setFillColor(sf::Color::Yellow);
	text2.setOutlineColor(sf::Color::Black);
	text2.setOutlineThickness(3);
	Utils::SetOrigin(text2, Origins::MC);

	text3.setFont(font);
	text3.setLetterSpacing(0.2);
	text3.setCharacterSize(accentTextSize);
	text3.setFillColor(sf::Color::Yellow);
	text3.setOutlineColor(sf::Color::Black);
	text3.setOutlineThickness(3);
	Utils::SetOrigin(text3, Origins::MC);

	body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
	body.setScale(1, 1);
	Utils::SetOrigin(body, Origins::MC);
	body.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f + 45.f });

	text1.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f });
}

void TutoUi::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		++tutoIndex;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		--tutoIndex;
	}
	if (tutoIndex < 0)
	{
		tutoIndex = 0;
	}
	if (tutoIndex == 0)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));

		text1.setString(L"조작키는 방향키 " + text2.getString() + L" 와 " + text3.getString() + L" 입니다.");
	}
}

void TutoUi::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(text1);
}
