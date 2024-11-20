#include "stdafx.h"
#include "aniinstrument.h"
#include "SceneGame.h"

aniinstrument::aniinstrument(const std::string& name)
	: GameObject(name)
{
}

void aniinstrument::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	drumBody.setPosition(position);
	bassBody.setPosition(position);
	castanetsBody.setPosition(position);
}

void aniinstrument::SetRotation(float angle)
{
	rotation = angle;
	drumBody.setRotation(rotation);
	bassBody.setRotation(rotation);
	castanetsBody.setRotation(rotation);
}

void aniinstrument::SetScale(const sf::Vector2f& s)
{
	scale = s;
	drumBody.setScale(scale);
	bassBody.setScale(scale);
	castanetsBody.setScale(scale);
}

void aniinstrument::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(drumBody, originPreset);
		Utils::SetOrigin(bassBody, originPreset);
		Utils::SetOrigin(castanetsBody, originPreset);
	}
}

void aniinstrument::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void aniinstrument::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;

	drumAnimator.SetTarget(&drumBody);
	bassAnimator.SetTarget(&bassBody);
	castanetsAnimator.SetTarget(&castanetsBody);
	
	drumAnimator.SetSpeed(1.f);
	bassAnimator.SetSpeed(1.f);
	castanetsAnimator.SetSpeed(1.f);

	std::string sheetId = "graphics/drum_ani.png";
	{
		sf::IntRect coord(0, 0, 296, 367);

		drum.loadFromFile("Animations/drum.csv");
	}
	std::string sheetId2 = "graphics/bass_ani.png";
	{
		sf::IntRect coord2(0, 0, 306, 354);

		drum.loadFromFile("Animations/bass.csv");
	}
	//std::string sheetId3 = "graphics/bass_ani.png";
	//{
	//	sf::IntRect coord3(0, 0, 296, 367);
	//
	//	drum.loadFromFile("Animations/drum.csv");
	//}
}

void aniinstrument::Release()
{
}

void aniinstrument::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	//drumAnimator.Play(&drum);
	//bassAnimator.Play(&drum);
	//castanetsAnimator.Play(&drum);
	SetOrigin(Origins::MC);
}

void aniinstrument::Update(float dt)
{
	drumAnimator.Update(dt);
	bassAnimator.Update(dt);
	//castanetsAnimator.Update(dt);
	int anispawn = Utils::RandomRange(1, 2);
	sf::Vector2f pos;
	if (sceneGame->GetdrumOn() == true && sceneGame->GetSpawnDelay() - 0.5f > sceneGame->GetMaxDelay())
	{
		drumAnimator.Play(&drum);
		if (anispawn == 1 )
		{
			pos.x = Utils::RandomRange(0.f + 100.f, 625.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		else
		{
			pos.x = Utils::RandomRange(1295.f + 100.f, 1950.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		drumBody.setPosition(pos);
	}
	else
	{
		drumAnimator.Stop();
	}
	if (sceneGame->GetbassOn() == true && sceneGame->GetSpawnDelay() - 0.5f > sceneGame->GetMaxDelay())
	{
		bassAnimator.Play(&bass);
		if (anispawn == 1)
		{
			pos.x = Utils::RandomRange(0.f + 100.f, 625.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		else
		{
			pos.x = Utils::RandomRange(1295.f + 100.f, 1950.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		bassBody.setPosition(pos);
	}
	else
	{
		bassAnimator.Stop();
	}
	if (sceneGame->GetcastanetsOn() == true && sceneGame->GetSpawnDelay() - 0.5f > sceneGame->GetMaxDelay())
	{
		castanetsAnimator.Play(&castanets);
		if (anispawn == 1)
		{
			pos.x = Utils::RandomRange(0.f + 100.f, 625.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		else
		{
			pos.x = Utils::RandomRange(1295.f + 100.f, 1950.f - 100.f);
			pos.y = Utils::RandomRange(0.f + 100.f, 1080.f - 100.f);
		}
		castanetsBody.setPosition(pos);
	}
	else
	{
		castanetsAnimator.Stop();
	}

}

void aniinstrument::Draw(sf::RenderWindow& window)
{
	if (sceneGame->GetdrumOn() == true)
	{
		window.draw(drumBody);
	}
	if (sceneGame->GetbassOn() == true)
	{
		window.draw(bassBody);
	}
	//if (sceneGame->GetcastanetsOn() == true)
	//{
	//	window.draw(castanetsBody);
	//}
}
