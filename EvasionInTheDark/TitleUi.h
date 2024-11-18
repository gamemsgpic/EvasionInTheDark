#pragma once
class SceneStart;

class TitleUi : public GameObject
{
protected:
	SceneStart* scenestart;

	sf::Vector2i mousePos;

	sf::Sprite gameStart;
	std::string textureId = "graphics/title_Start.png";

	float colorChange = 0.f;
	float changedelay = 0.5f;
public:
	TitleUi(const std::string& name = "");
	~TitleUi() = default;

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

