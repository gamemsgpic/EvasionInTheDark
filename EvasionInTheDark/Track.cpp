#include "stdafx.h"
#include "Track.h"
#include "Player.h"
#include "SceneGame.h"

Track::Track(const std::string& name)
	: GameObject(name)
{
}

void Track::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Track::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Track::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

sf::FloatRect Track::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Track::GetGlobalBounds() const
{
	return body.getLocalBounds();
}

void Track::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Track::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Track::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Track::Release()
{
}

void Track::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(Origins::MC);
	SetScale({ 1, 1 });
	SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.5f });
}

void Track::Update(float dt)
{
	sound1Start += dt;
	sound2Start += dt;
	sound3Start += dt;
	if (player->GetCurrentTrack() == 1)
	{
		if (sound1Start >= soundDelay)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/left.wav"), false)->setVolume(0.5f);
			sound1Start = 0.f;
			sound2Start = 5.f;
			sound3Start = 5.f;
		}
	}
	if (player->GetCurrentTrack() == 2)
	{
		if (sound2Start >= soundDelay)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/mid.wav"), false)->setVolume(0.5f);
			sound2Start = 0.f;
			sound1Start = 5.f;
			sound3Start = 5.f;
		}
	}
	if (player->GetCurrentTrack() == 3)
	{
		if (sound3Start >= soundDelay)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/right.wav"), false)->setVolume(0.5f);
			sound3Start = 0.f;
			sound1Start = 5.f;
			sound2Start = 5.f;
		}
	}
}

void Track::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}