#pragma once

class TutoUi : public GameObject
{
protected:

	sf::Sprite body;

	int tutoIndex = 0;

	sf::Text text;

	sf::Sound sound;

	bool bassPlay = true;
	bool drumPlay = true;
	bool castanetsPlay = true;
	bool explain = true;

	float explainStart = 4.f;
	float explainEnd = 4.f;
	float soundTrigger1 = 5.f;
	float soundTrigger2 = 5.f;
	float soundTrigger3 = 5.f;
	float soundStartTrigger = 0.f;
	float soundStartDelay = 5.f;
	float soundDelay = 5.f;

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

	void PlayBass();
	void PlayDrum();
	void PlayCastanets();
};

