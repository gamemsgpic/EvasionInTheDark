#pragma once

class TutoUi : public GameObject
{
protected:
	sf::Sprite body;

	int tutoIndex = 0;

	sf::Text text1;
	sf::Text text2;
	sf::Text text3;

public:
	TutoUi(const std::string& name = "");
	~TutoUi() = default;

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

