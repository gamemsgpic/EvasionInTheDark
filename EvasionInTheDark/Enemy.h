#pragma once

class Track;

class Enemy : public GameObject
{
public:
	enum class Types
	{
		Bass,
		Castanets,
		Drum,
	};

	static const int TotalTypes = 3;
protected:
	Types types = Types::Bass;

	sf::Sprite body;
	std::string textureId;
	sf::Vector2f currentPos;
	sf::Vector2f gravity = { 0.f, 300.f };

	sf::CircleShape enemyHitBox;

	Track* track;

	sf::Sound* sound;

	bool enemyDie = false;


public:
	Enemy(const std::string& name = "");
	~Enemy() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetHitBoxOrigin(sf::Vector2f& hitorigin);
	void SetHitBoxPosition(sf::Vector2f& hitposition);

	void SetSoundStop() { sound->stop(); }

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	void ChangeEnemyDie(bool change) { enemyDie = change; }
	bool GetEnemyDie() { return enemyDie; }

	float GetEnemyRadius() { return enemyHitBox.getRadius(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
	void GravityUp() { gravity.y += 25.f; }
};
