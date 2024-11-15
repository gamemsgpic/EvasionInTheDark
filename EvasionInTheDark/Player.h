#pragma once

class Track;
class Enemy;
class SceneGame;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/player.png";
	sf::Color playercolor;
	sf::CircleShape hitBox;
	sf::Vector2f currentPos;

	int life = 0;
	int currentTrack = 2;

	int score = 0;
	int levelPoint = 0;
	int level = 0;
	int bestScore = 0;

	float damage = 3.f;
	float damageDelay = 3.f;

	bool playerDie = false;
	//bool hit = false;

	Track* track;
	Enemy* enemy;
	SceneGame* scenegame;

public:
	Player(const std::string& name = "");
	~Player() = default;


	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	int GetCurrentTrack() { return currentTrack; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	//void ChangeHit(bool boom) { hit = boom; }
	//bool GetHit() { return hit; }

	void LifeUp();
	void LevelPointUp() { ++levelPoint; }
	void SetScore() { ++score; }
	int GetScore() { return score; }
	int GetBestScore() { return bestScore; }
	int GetLife() { return life; }
};
