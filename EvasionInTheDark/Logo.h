#pragma once

class Logo : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/logo.png";

	float changeLogo = 0.f;
	float changeLogoDelay = 0.f;

	float angle = 0.f;

	bool angledir = false;

	bool changeLogoswitch = false;
public:
	Logo(const std::string& name = "");
	~Logo() = default;

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


