#pragma once
#include "AnimationClip.h"

class SceneGame;

class aniinstrument : public GameObject
{
protected:
	SceneGame* sceneGame;

	sf::Sprite drumBody;
	sf::Sprite bassBody;
	sf::Sprite castanetsBody;
	Animator drumAnimator;
	Animator bassAnimator;
	Animator castanetsAnimator;

	AnimationClip drum;
	AnimationClip bass;
	AnimationClip castanets;

	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f velocity = { 0.f, 0.f };

	float speed = 600.f;

public:
	aniinstrument(const std::string& name = "");
	~aniinstrument() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

