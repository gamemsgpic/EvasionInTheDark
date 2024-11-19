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

	//hit = false;


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
	currentPos = { 1920 * 0.5f,
		1080 - body.getGlobalBounds().height * 0.5f - 20.f };
	SetPosition(currentPos);
	hitBox.setOrigin(GetOrigin());
	hitBox.setPosition(currentPos);

	currentTrack = 1;
	score = 0;
	life = 3;

	if (easy == true)
	{
		triggerLevelPoint = 5;
		maxLevel = 8;
		lifeUpTrigger = 10;
	}
	if (normal == true)
	{
		triggerLevelPoint = 3;
		maxLevel = 12;
		level = 4;
		lifeUpTrigger = 15;
	}
	if (extreme == true)
	{
		triggerLevelPoint = 1;
		maxLevel = 100;
		level = 8;
		lifeUpTrigger = 20;
	}

}

void Player::Update(float dt)
{
	damage += dt;
	if (score > easyBestScore && easy == true)
	{
		easyBestScore = score;
	}
	if (score > normalBestScore && normal == true)
	{
		normalBestScore = score;
	}
	if (score > extremeBestScore && extreme == true)
	{
		extremeBestScore = score;
	}
	//if (score > 2)
	//{
	//	spawnChange = true;
	//}

	if (currentTrack < 2)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			currentPos.x += track->GetGlobalBounds().width;
			SetPosition(currentPos);
			++currentTrack;
		}
	}

	if (currentTrack > 0)
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
			if (damage > damageDelay)
			{
				SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/damage.wav"))->setVolume(3.f);
				--life;
				enemy->ChangeHit(true);
				damage = 0.f;
				playerhit = true;
			}
		}
	}
	if (levelPoint == triggerLevelPoint)
	{
		++level;
		++count;
		scenegame->SpawnSpeedUp();
		levelPoint = 0;
	}
	if (count == lifeUpTrigger)
	{
		if (life < 3)
		{
			++life;
			count = 0;
		}
	}
	if (level > maxLevel)
	{
		level = maxLevel;
	}
	if (life == 0)
	{
		playerDie = true;
		//spawnChange = false;
	}
	else
	{
		playerDie = false;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (scenegame->GetHitBoxAct() == true)
	{
		window.draw(hitBox);
	}
}

void Player::LifeUp()
{
	if (life < 3)
	{
		++life;
	}
}
