#include "stdafx.h"
#include "Enemy.h"
#include "SceneGame.h"
#include "Track.h"

Enemy::Enemy(const std::string& name)
	: GameObject(name)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Enemy::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Enemy::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Enemy::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Enemy::SetHitBoxOrigin(sf::Vector2f& hitorigin)
{

}

void Enemy::SetHitBoxPosition(sf::Vector2f& hitposition)
{
}

sf::FloatRect Enemy::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Enemy::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Enemy::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	track = dynamic_cast<Track*>(SCENE_MGR.GetCurrentScene()->FindGo("Track"));
}

void Enemy::Update(float dt)
{
	SetPosition({ position + gravity * dt });
	enemyHitBox.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(enemyHitBox);
}

void Enemy::SetType(Types type)
{
	sf::Vector2f enemyCurrentPos = { FRAMEWORK.GetWindowSizeF().x * 0.5f,
			FRAMEWORK.GetWindowSizeF().y * 0.5f };
	sf::Vector2f hitorigin = { FRAMEWORK.GetWindowSizeF().x * 0.5f,
			FRAMEWORK.GetWindowSizeF().y * 0.5f };
	this->types = type;
	switch (this->types)
	{
	case Types::Bass:
		textureId = "graphics/enemybass.png";
		body.setPosition(enemyCurrentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(enemyCurrentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound = SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/bass.wav"), true);
		sound->setVolume(15.f);
		break;
	case Types::Castanets:
		textureId = "graphics/enemycastanets.png";
		body.setPosition(enemyCurrentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(enemyCurrentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound = SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/castanets.wav"), true);
		sound->setVolume(15.f);
		break;
	case Types::Drum:
		textureId = "graphics/enemydrum.png";
		body.setPosition(enemyCurrentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(enemyCurrentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound = SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/drum.wav"), true);
		sound->setVolume(15.f);
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	Utils::SetOrigin(enemyHitBox, Origins::MC);
}
