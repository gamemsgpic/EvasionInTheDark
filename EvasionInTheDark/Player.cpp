#include "stdafx.h"
#include "Player.h"
#include "Track.h"
#include "Enemy.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Player::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	hitBox.setOrigin(origin);
	hitBox.setPosition(position);
	hitBox.setRadius(64);
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Green);
	hitBox.setOutlineThickness(2);

}

void Player::Release()
{
}

void Player::Reset()
{
	track = dynamic_cast<Track*>(SCENE_MGR.GetCurrentScene()->FindGo("Track"));
	enemy = dynamic_cast<Enemy*>(SCENE_MGR.GetCurrentScene()->FindGo("Enemy"));
	scenegame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	TEXTURE_MGR.Get(textureId).setSmooth(true);
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(Origins::MC);
	SetScale({ 1, 1 });
	currentPos = { FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y - body.getGlobalBounds().height * 0.5f - 20.f };
	SetPosition(currentPos);
	hitBox.setOrigin(GetOrigin());
	hitBox.setPosition(currentPos);

	

}

void Player::Update(float dt)
{
	if (currentTrack < 3)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			currentPos.x += track->GetGlobalBounds().width;
			SetPosition(currentPos);
			++currentTrack;
		}
	}

	if (currentTrack > 1)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			currentPos.x -= track->GetGlobalBounds().width;
			SetPosition(currentPos);
			--currentTrack;
		}
	}
	hitBox.setPosition(currentPos);

	const auto& list = scenegame->GetEnemyList();
	for (auto& enemy : list)
	{
		if (!enemy->IsActive())
		{
			continue;
		}
		float circles = (hitBox.getRadius() + hitBox.getRadius()) *
			(enemy->GetEnemyRadius() + enemy->GetEnemyRadius());
		float circlesPos = ((enemy->GetPosition().x - GetPosition().x) *
			(enemy->GetPosition().x - GetPosition().x) +
			(enemy->GetPosition().y - GetPosition().y) *
			(enemy->GetPosition().y - GetPosition().y));
		if (circlesPos < circles)
		{
			--life;
			hit = true;
		}
	}
	if (levelPoint == 10)
	{
		++level;
		enemy->GravityUp();
		scenegame->SpawnSpeedUp();
		levelPoint = 0;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(hitBox);
}

void Player::LifeUp()
{
	if (life < 3)
	{
		++life;
	}
}
