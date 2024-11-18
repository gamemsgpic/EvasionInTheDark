#include "stdafx.h"
#include "Logo.h"

Logo::Logo(const std::string& name)
	: GameObject(name)
{
}

void Logo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Logo::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Logo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Logo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Logo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Logo::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	changeLogoDelay = Utils::RandomRange(2.f,4.f);
	changeLogoswitch = Utils::RandomRange(0, 1);
	
}

void Logo::Release()
{
}

void Logo::Reset()
{
	TEXTURE_MGR.Get(textureId).setSmooth(true);
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	body.setTextureRect(sf::IntRect(0, 0, 256, 330));
	Utils::SetOrigin(body, Origins::MC);
	body.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f , FRAMEWORK.GetWindowSizeF().y * 0.8f);
	body.setScale(1.f, 1.f);
	body.setRotation(-45.f * angle);
	body.setOrigin(origin.x + 128.f, origin.y + 660.f);
}

void Logo::Update(float dt)
{
	if (angledir)
	{
		rotation = rotation += -dt * Utils::RandomRange(10.f, 50.f);
	}
	else
	{
		rotation = rotation += dt * Utils::RandomRange(10.f, 50.f);
	}

	if ((rotation < -45.f && angledir )||  (rotation > 45.f && !angledir))
	{ 
		angledir = !angledir;
	}

	body.setRotation(rotation);
	changeLogo += dt;
	changeLogoDelay = Utils::RandomRange(3.f, 5.f);
	changeLogoswitch = Utils::RandomRange(0, 1);
	float min = 1.f;
	float diff = 0.3f;
	body.setScale({ min + diff * sinf(4.0f * Framework::Instance().GetRealTime()), 
		min + diff * sinf(4.0f * Framework::Instance().GetRealTime()) });
	// body.setRotation(min + diff * sinf(4.0f * Framework::Instance().GetRealTime()));
	if (changeLogo > changeLogoDelay)
	{
		if (changeLogoswitch)
		{
			body.setTextureRect(sf::IntRect(0, 0, 256, 330));
		}
		else
		{
			body.setTextureRect(sf::IntRect(256, 0, 256, 330));
		}
		changeLogo = 0.f;
	}
}

void Logo::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
