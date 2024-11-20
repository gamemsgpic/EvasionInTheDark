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

	sf::Vector2f direction1 = { 0.f, 0.f };
	sf::Vector2f direction2 = { 0.f, 0.f };
	sf::Vector2f direction3 = { 0.f, 0.f };

	sf::RectangleShape test;
	sf::RectangleShape test2;

	float speed = 500.f;

	int drumPos = 0;
	int bassPos = 0;
	int castanetsPos = 0;

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

	void SetPosDrum(int s);
	void SetPosBass(int s);
	void SetPosCastanets(int s);
};

