#pragma once

class SceneGame;
class Track;
class Player;

class UiHud : public GameObject
{
protected:
	SceneGame* sceneGame;
	Track* track;
	Player* player;

	sf::Text textScore;
	sf::Text textHighScore;
	sf::Text textLife;

	sf::Sprite iconLight;
public:
	UiHud(const std::string& name = "");
	~UiHud() = default;

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

	void SetScore(int s);
	void SetHiScore(int s);
	void SetLife(int current);
};
