#pragma once

class Track;

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

	bool soundStop = false;

	Track* track;

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

	void LifeUp();
};