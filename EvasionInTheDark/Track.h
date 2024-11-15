#pragma once

class Player;
class SceneGame;

class Track : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/track.png";

	float sound1Start = 5.f;
	float sound2Start = 5.f;
	float sound3Start = 5.f;
	float soundDelay = 5.f;


	Player* player;
	SceneGame* sceneGame;
public:
	Track(const std::string& name = "");
	~Track() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
