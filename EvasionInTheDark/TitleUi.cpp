#include "stdafx.h"
#include "TitleUi.h"
#include "Player.h"

TitleUi::TitleUi(const std::string& name)
{
}

void TitleUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TitleUi::SetRotation(float angle)
{
	rotation = angle;
}

void TitleUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TitleUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
	}
}

void TitleUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TitleUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	player->SetNormal(true);
	normal.setColor(sf::Color(Utils::RandomColor()));
}

void TitleUi::Release()
{

}

void TitleUi::Reset()
{
	float textSize = 18.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	textEasyBestScore.setFont(font);
	textEasyBestScore.setLetterSpacing(0.2);
	textEasyBestScore.setCharacterSize(textSize);
	textEasyBestScore.setFillColor(sf::Color::White);
	textEasyBestScore.setOutlineThickness(2);
	Utils::SetOrigin(textEasyBestScore, Origins::MC);

	textNormalBestScore.setFont(font);
	textNormalBestScore.setLetterSpacing(0.2);
	textNormalBestScore.setCharacterSize(textSize);
	textNormalBestScore.setFillColor(sf::Color::White);
	textNormalBestScore.setOutlineThickness(2);
	Utils::SetOrigin(textNormalBestScore, Origins::MC);

	textExtremeBestScore.setFont(font);
	textExtremeBestScore.setLetterSpacing(0.2);
	textExtremeBestScore.setCharacterSize(textSize);
	textExtremeBestScore.setFillColor(sf::Color::White);
	textExtremeBestScore.setOutlineThickness(2);
	Utils::SetOrigin(textExtremeBestScore, Origins::MC);

	TEXTURE_MGR.Get(textureId).setSmooth(true);
	gameStart.setTexture(TEXTURE_MGR.Get(textureId));
	gameStart.setScale(1.f, 1.f);
	Utils::SetOrigin(gameStart, Origins::MC);

	easy.setTexture(TEXTURE_MGR.Get("graphics/easy.png"));
	easy.setScale(0.5f, 0.5f);
	Utils::SetOrigin(easy, Origins::MC);

	normal.setTexture(TEXTURE_MGR.Get("graphics/normal.png"));
	normal.setScale(0.5f, 0.5f);
	Utils::SetOrigin(normal, Origins::MC);

	extreme.setTexture(TEXTURE_MGR.Get("graphics/extreme.png"));
	extreme.setScale(0.5f, 0.5f);
	Utils::SetOrigin(extreme, Origins::MC);


	textEasyBestScore.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.4f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f - easy.getGlobalBounds().height + 15.f);
	textNormalBestScore.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f - easy.getGlobalBounds().height + 15.f);
	textExtremeBestScore.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.6f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f - easy.getGlobalBounds().height + 15.f);
	gameStart.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.85f);
	easy.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.4f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);
	normal.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.5f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);
	extreme.setPosition(FRAMEWORK.GetWindowSizeF().x * 0.6f,
		FRAMEWORK.GetWindowSizeF().y * 0.7f);

	SetEasyHiScore(player->GetEasyBestScore());
	SetNormalHiScore(player->GetNormalBestScore());
	SetExtremeHiScore(player->GetExtremeBestScore());

	explainStart = 120.f;
}

void TitleUi::Update(float dt)
{
	colorChange += dt;
	explainStart += dt;

	if (explainStart > explainEnd)
	{
		SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/title.wav"))->setVolume(20.f);
		explainStart = 0.f;
	}

	mousePos = InputMgr::GetMousePosition();
	sf::Vector2f pos = SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos);
	if (gameStart.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		if (colorChange > changedelay)
		{
			gameStart.setColor(sf::Color(Utils::RandomColor()));
			colorChange = 0.f;
		}
	}
	else
	{
		gameStart.setColor(sf::Color::White);
	}

	if (easy.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(true);
			player->SetNormal(false);
			player->SetExtreme(false);
			easy.setColor(sf::Color(Utils::RandomColor()));
			normal.setColor(sf::Color::White);
			extreme.setColor(sf::Color::White);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad1))
	{
		SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/easy.wav"))->setVolume(20.f);
		player->SetEasy(true);
		player->SetNormal(false);
		player->SetExtreme(false);
		easy.setColor(sf::Color(Utils::RandomColor()));
		normal.setColor(sf::Color::White);
		extreme.setColor(sf::Color::White);
	}

	if (normal.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(false);
			player->SetNormal(true);
			player->SetExtreme(false);
			normal.setColor(sf::Color(Utils::RandomColor()));
			easy.setColor(sf::Color::White);
			extreme.setColor(sf::Color::White);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad2))
	{
		SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/normal.wav"))->setVolume(20.f);
		player->SetEasy(false);
		player->SetNormal(true);
		player->SetExtreme(false);
		normal.setColor(sf::Color(Utils::RandomColor()));
		easy.setColor(sf::Color::White);
		extreme.setColor(sf::Color::White);
	}

	if (extreme.getGlobalBounds().contains(pos))
	{

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			player->SetEasy(false);
			player->SetNormal(false);
			player->SetExtreme(true);
			extreme.setColor(sf::Color(Utils::RandomColor()));
			easy.setColor(sf::Color::White);
			normal.setColor(sf::Color::White);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad3))
	{
		SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/extreme.wav"))->setVolume(20.f);
		player->SetEasy(false);
		player->SetNormal(false);
		player->SetExtreme(true);
		extreme.setColor(sf::Color(Utils::RandomColor()));
		easy.setColor(sf::Color::White);
		normal.setColor(sf::Color::White);
	}
}

void TitleUi::Draw(sf::RenderWindow& window)
{
	window.draw(gameStart);
	window.draw(easy);
	window.draw(normal);
	window.draw(extreme);
	window.draw(textEasyBestScore);
	window.draw(textNormalBestScore);
	window.draw(textExtremeBestScore);
}

void TitleUi::SetEasyHiScore(int s)
{
	textEasyBestScore.setString("HI SCORE: " + std::to_string(s));
	Utils::SetOrigin(textEasyBestScore, Origins::MC);
}
void TitleUi::SetNormalHiScore(int s)
{
	textNormalBestScore.setString("HI SCORE: " + std::to_string(s));
	Utils::SetOrigin(textNormalBestScore, Origins::MC);
}
void TitleUi::SetExtremeHiScore(int s)
{
	textExtremeBestScore.setString("HI SCORE: " + std::to_string(s));
	Utils::SetOrigin(textExtremeBestScore, Origins::MC);
}

void TitleUi::SetExplainStart()
{
	explainStart = 5.f;
}
