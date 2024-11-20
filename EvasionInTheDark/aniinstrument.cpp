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

	drumBody.setScale(0.5f, 0.5f);
	bassBody.setScale(0.7f, 0.7f);
	castanetsBody.setScale(0.5f, 0.5f);

	drumAnimator.SetSpeed(1.f);
	bassAnimator.SetSpeed(1.f);
	castanetsAnimator.SetSpeed(1.f);

	std::string sheetId = "graphics/drum_ani.png";
	{
		sf::IntRect coord(0, 0, 205, 253);

		drum.loadFromFile("Animations/drum.csv");
	}
	std::string sheetId2 = "graphics/bass_ani.png";
	{
		sf::IntRect coord2(0, 0, 306, 354);

		bass.loadFromFile("Animations/bass.csv");
	}

	std::string sheetId3 = "graphics/castanets_ani.png";
	{
		sf::IntRect coord3(0, 0, 256, 335);
	
		castanets.loadFromFile("Animations/castanets.csv");
	}

	SetPosDrum(Utils::RandomRange(1, 2));
	SetPosBass(Utils::RandomRange(1, 2));
	SetPosCastanets(Utils::RandomRange(1, 2));

	drumAnimator.Play(&drum);
	bassAnimator.Play(&bass);
	castanetsAnimator.Play(&castanets);
}

void aniinstrument::Release()
{
}

void aniinstrument::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	SetOrigin(Origins::MC);

	float angle1 = Utils::RandomRange(-3.14f, 3.14f) * 3.f / 2.f + Utils::RandomRange(-3.14f, 3.14f) * 0.3f;
	direction1 = { cos(angle1), sin(angle1) };
	float angle2 = Utils::RandomRange(-3.14f, 3.14f) * 3.f / 2.f + Utils::RandomRange(-3.14f, 3.14f) * 0.3f;
	direction2 = { cos(angle2), sin(angle2) };
	float angle3 = Utils::RandomRange(-3.14f, 3.14f) * 3.f / 2.f + Utils::RandomRange(-3.14f, 3.14f) * 0.3f;
	direction3 = { cos(angle3), sin(angle3) };


}

void aniinstrument::Update(float dt)
{
	auto newPos1 = drumBody.getPosition() + direction1 * speed * dt;
	auto newPos2 = bassBody.getPosition() + direction2 * speed * dt;
	auto newPos3 = castanetsBody.getPosition() + direction3 * speed * dt;
	drumBody.setPosition(newPos1);
	bassBody.setPosition(newPos2);
	castanetsBody.setPosition(newPos3);
	drumAnimator.Update(dt);
	bassAnimator.Update(dt);
	castanetsAnimator.Update(dt);

	colorChangeTrigger += dt;
	crashTrigger1 += dt;
	crashTrigger2 += dt;
	crashTrigger3 += dt;
	
	if (colorChangeTrigger > colorChangeDelay)
	{
		drumBody.setColor(Utils::RandomColor());
		bassBody.setColor(Utils::RandomColor());
		castanetsBody.setColor(Utils::RandomColor());
		colorChangeTrigger = 0.f;
	}

	if (drumPos == 1 && crashTrigger1 > crashDelay)
	{
		if (newPos1.y < 0.f + drumBody.getGlobalBounds().height * 0.5f)
		{
			newPos1.y = 0.f;
			newPos1.y += drumBody.getGlobalBounds().height * 0.8f;
			direction1.y *= -1.f;
		}
		else if (newPos1.y > 1080.f - drumBody.getGlobalBounds().height * 0.5f)
		{
			newPos1.y = 1080.f;
			newPos1.y -= drumBody.getGlobalBounds().height * 0.8f;
			direction1.y *= -1.f;
		}

		if (newPos1.x < 0.f + drumBody.getGlobalBounds().width * 0.5f)
		{
			newPos1.x = 0.f;
			newPos1.x += drumBody.getGlobalBounds().width * 0.8f;
			direction1.x *= -1.f;
		}
		else if (newPos1.x > 620.f - drumBody.getGlobalBounds().width * 0.5f)
		{
			newPos1.x = 620.f;
			newPos1.x -= drumBody.getGlobalBounds().width * 0.8f;
			direction1.x *= -1.f;
		}
	}
	else
	{
		if (newPos1.y < 0.f + drumBody.getGlobalBounds().height * 0.5f)
		{
			newPos1.y = 0;
			newPos1.y += drumBody.getGlobalBounds().height * 0.8f;
			direction1.y *= -1.f;
		}
		else if (newPos1.y > 1080.f - drumBody.getGlobalBounds().height * 0.5f)
		{
			newPos1.y = 1080.f;
			newPos1.y -= drumBody.getGlobalBounds().height * 0.8f;
			direction1.y *= -1.f;
		}
		if (newPos1.x < 1300.f + drumBody.getGlobalBounds().width * 0.5f)
		{
			newPos1.x = 1300.f;
			newPos1.x += drumBody.getGlobalBounds().width * 0.8f;
			direction1.x *= -1.f;
		}
		else if (newPos1.x > 1920.f - drumBody.getGlobalBounds().width * 0.5f)
		{
			newPos1.x = 1920.f;
			newPos1.x -= drumBody.getGlobalBounds().width * 0.8f;
			direction1.x *= -1.f;
		}
		drumBody.setPosition(newPos1);
	}

	if (bassPos == 1 && crashTrigger1 > crashDelay)
	{
		if (newPos2.y < 0.f + bassBody.getGlobalBounds().height * 0.5f)
		{
			newPos2.y = 0.f;
			newPos2.y += bassBody.getGlobalBounds().height * 0.8f;
			direction2.y *= -1.f;
		}
		else if (newPos2.y > 1080.f - bassBody.getGlobalBounds().height * 0.5f)
		{
			newPos2.y = 1080.f;
			newPos2.y -= bassBody.getGlobalBounds().height * 0.8f;
			direction2.y *= -1.f;
		}

		if (newPos2.x < 0.f + bassBody.getGlobalBounds().width * 0.5f)
		{
			newPos2.x = 0.f;
			newPos2.x += bassBody.getGlobalBounds().width * 0.8f;
			direction2.x *= -1.f;
		}
		else if (newPos2.x > 620.f - bassBody.getGlobalBounds().width * 0.5f)
		{
			newPos2.x = 620.f;
			newPos2.x -= bassBody.getGlobalBounds().width * 0.8f;
			direction2.x *= -1.f;
		}
	}
	else
	{
		if (newPos2.y < 0.f + bassBody.getGlobalBounds().height * 0.5f)
		{
			newPos2.y = 0.f;
			newPos2.y += bassBody.getGlobalBounds().height * 0.8f;
			direction2.y *= -1.f;
		}
		else if (newPos2.y > 1080.f - bassBody.getGlobalBounds().height * 0.5f)
		{
			newPos2.y = 1080;
			newPos2.y -= bassBody.getGlobalBounds().height * 0.8f;
			direction2.y *= -1.f;
		}
		if (newPos2.x < 1300.f + bassBody.getGlobalBounds().width * 0.5f)
		{
			newPos2.x = 1300.f;
			newPos2.x += bassBody.getGlobalBounds().width * 0.8f;
			direction2.x *= -1.f;
		}
		else if (newPos2.x > 1920.f - bassBody.getGlobalBounds().width * 0.5f)
		{
			newPos2.x = 1920.f;
			newPos2.x -= bassBody.getGlobalBounds().width * 0.8f;
			direction2.x *= -1.f;
		}
		bassBody.setPosition(newPos2);
	}

	if (castanetsPos == 1 && crashTrigger1 > crashDelay)
	{
		if (newPos3.y < 0.f + castanetsBody.getGlobalBounds().height * 0.5f)
		{
			newPos3.y = 0.f;
			newPos3.y += castanetsBody.getGlobalBounds().height * 0.8f;
			direction3.y *= -1.f;
		}
		else if (newPos3.y > 1080.f - castanetsBody.getGlobalBounds().height * 0.5f)
		{
			newPos3.y = 1080.f;
			newPos3.y -= castanetsBody.getGlobalBounds().height * 0.8f;
			direction3.y *= -1.f;
		}

		if (newPos3.x < 0.f + castanetsBody.getGlobalBounds().width * 0.5f)
		{
			newPos3.x = 0.f;
			newPos3.x += castanetsBody.getGlobalBounds().width * 0.8f;
			direction3.x *= -1.f;
		}
		else if (newPos3.x > 620.f - castanetsBody.getGlobalBounds().width * 0.5f)
		{
			newPos3.x = 620.f;
			newPos3.x -= castanetsBody.getGlobalBounds().width * 0.8f;
			direction3.x *= -1.f;
		}
	}
	else
	{
		if (newPos3.y < 0.f + castanetsBody.getGlobalBounds().height * 0.5f)
		{
			newPos3.y = 0.f;
			newPos3.y += castanetsBody.getGlobalBounds().height * 0.8f;
			direction3.y *= -1.f;
		}
		else if (newPos3.y > 1080.f - castanetsBody.getGlobalBounds().height * 0.5f)
		{
			newPos3.y = 1080;
			newPos3.y -= castanetsBody.getGlobalBounds().height * 0.8f;
			direction3.y *= -1.f;
		}
		if (newPos3.x < 1300.f + castanetsBody.getGlobalBounds().width * 0.5f)
		{
			newPos3.x = 1300.f;
			newPos3.x += castanetsBody.getGlobalBounds().width * 0.8f;
			direction3.x *= -1.f;
		}
		else if (newPos3.x > 1920.f - castanetsBody.getGlobalBounds().width * 0.5f)
		{
			newPos3.x = 1920.f;
			newPos3.x -= castanetsBody.getGlobalBounds().width * 0.8f;
			direction3.x *= -1.f;
		}
		castanetsBody.setPosition(newPos3);
	}
}

void aniinstrument::Draw(sf::RenderWindow& window)
{
	window.draw(test);
	window.draw(test2);
	if (sceneGame->GetdrumOn() == true)
	{
		window.draw(drumBody);
	}
	if (sceneGame->GetbassOn() == true)
	{
		window.draw(bassBody);
	}
	if (sceneGame->GetcastanetsOn() == true)
	{
		window.draw(castanetsBody);
	}
}

void aniinstrument::SetPosDrum(int s)
{
	sf::Vector2f pos;
	if (s == 1)
	{
		pos.x = Utils::RandomRange(0.f + 300.f, 620.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	else
	{
		pos.x = Utils::RandomRange(1300.f + 300.f, 1920.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	drumBody.setPosition(pos);

	drumPos = s;

}

void aniinstrument::SetPosBass(int s)
{
	sf::Vector2f pos;
	if (s == 1)
	{
		pos.x = Utils::RandomRange(0.f + 300.f, 620.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	else
	{
		pos.x = Utils::RandomRange(1300.f + 300.f, 1920.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	bassBody.setPosition(pos);

	bassPos = s;
}

void aniinstrument::SetPosCastanets(int s)
{
	sf::Vector2f pos;
	if (s == 1)
	{
		pos.x = Utils::RandomRange(0.f + 300.f, 620.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	else
	{
		pos.x = Utils::RandomRange(1300.f + 300.f, 1920.f - 300.f);
		pos.y = Utils::RandomRange(0.f + 300.f, 1080.f - 300.f);
	}
	castanetsBody.setPosition(pos);

	castanetsPos = s;
}
