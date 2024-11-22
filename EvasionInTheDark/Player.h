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
	int currentTrack = 1;

	int score = 0;
	int levelPoint = 0;
	int level = 0;
	int triggerLevelPoint = 0;
	int maxLevel = 0;
	int count = 0;
	int lifeUpTrigger = 0;

	int easyBestScore = 0;
	int normalBestScore = 0;
	int extremeBestScore = 0;

	float damage = 1.f;
	float damageDelay = 1.f;
	
	bool playerDie = false;
	bool playerhit = false;
	bool spawnChange = false;

	bool easy = false;
	bool normal = false;
	bool extreme = false;

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

	void ChangePlayerHit(bool boom) { playerhit = boom; }
	bool GetPlayerHit() { return playerhit; }
	bool GetSpawnChange() { return spawnChange; }

	void LifeUp();
	void LevelPointUp() { ++levelPoint; }
	void SetScore() { ++score; }
	int GetLevel() { return level; }
	int GetScore() { return score; }
	int GetBestScore();
	int GetLife() { return life; }

	int GetEasyBestScore() { return easyBestScore; }
	int GetNormalBestScore() { return normalBestScore; }
	int GetExtremeBestScore() { return extremeBestScore; }

	bool GetEasy() { return easy; }
	bool GetNormal() { return normal; }
	bool GetExtreme() { return extreme; }
	void SetEasy(bool e) { easy = e; }
	void SetNormal(bool n) { normal = n; }
	void SetExtreme(bool ex) { extreme = ex; }

	bool SaveCsv(const std::string& filePath) const;
	bool LoadCsv(const std::string& filePath);
};
