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

	float connect = 0;
	globalvolume = SOUND_MGR.GetSfxVolume();
	connect = 28.f * globalvolume / 100;
	maxVolum = connect;
	currentVolum = maxVolum * 0.1f;
	enemyVolume = currentVolum;
	
	// enemyVolume =  * globalvolume / 100;

	sound.setPitch(1.5f);
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	track = dynamic_cast<Track*>(SCENE_MGR.GetCurrentScene()->FindGo("Track"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	gravity.y = 300.f;
}

void Enemy::Update(float dt)
{
	currentPos = position + gravity * dt;

	float volumePositionY = 900 - -384;

	enemyVolume = currentVolum + currentVolum * position.y * (position.y / volumePositionY) * 0.05f;

	if (enemyVolume > maxVolum)
	{
		enemyVolume = maxVolum;
	}

	sound.setVolume(enemyVolume);

	SetPosition(currentPos);
	enemyHitBox.setPosition(currentPos);

	colorChange += dt;
	if (colorChange > changedelay)
	{
		body.setColor(sf::Color(Utils::RandomColor()));
		colorChange = 0.f;
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (sceneGame->GetHitBoxAct() == true)
	{
		window.draw(enemyHitBox);
	}
}

void Enemy::SetType(Types type)
{
	this->types = type;
	switch (this->types)
	{
	case Types::Bass:
		textureId = "graphics/enemybass.png";
		body.setPosition(currentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(currentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/bass.wav"));
		sound.setLoop(true);
		sound.setVolume(enemyVolume);
		sound.play();
		break;
	case Types::Castanets:
		textureId = "graphics/enemycastanets.png";
		body.setPosition(currentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(currentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/castanets.wav"));
		sound.setLoop(true);
		sound.setVolume(enemyVolume);
		sound.play();
		break;
	case Types::Drum:
		textureId = "graphics/enemydrum.png";
		body.setPosition(currentPos);
		enemyHitBox.setRadius(64);
		enemyHitBox.setPosition(currentPos);
		enemyHitBox.setFillColor(sf::Color::Transparent);
		enemyHitBox.setOutlineColor(sf::Color::Green);
		enemyHitBox.setOutlineThickness(2);
		sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/drum.wav"));
		sound.setLoop(true);
		sound.setVolume(enemyVolume);
		sound.play();
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	Utils::SetOrigin(enemyHitBox, Origins::MC);
}
