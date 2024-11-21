#include "stdafx.h"
#include "TutoUi.h"

TutoUi::TutoUi(const std::string& name)
	: GameObject(name)
{
}

void TutoUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void TutoUi::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void TutoUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void TutoUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void TutoUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void TutoUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void TutoUi::Release()
{
}

void TutoUi::Reset()
{
	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/bgm.wav"), true);
	SoundMgr::Instance().SetBgmVolume(2.f);
	SoundMgr::Instance().PlayBgm("sound/bgm.wav");

	float textSize = 40.f;
	float accentTextSize = 43.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	text1.setFont(font);
	text1.setLetterSpacing(0.2);
	text1.setCharacterSize(textSize);
	text1.setFillColor(sf::Color::Yellow);
	text1.setOutlineColor(sf::Color::Black);
	text1.setOutlineThickness(3);
	Utils::SetOrigin(text1, Origins::MC);

	text2.setFont(font);
	text2.setLetterSpacing(0.2);
	text2.setCharacterSize(accentTextSize);
	text2.setFillColor(sf::Color::Yellow);
	text2.setOutlineColor(sf::Color::Black);
	text2.setOutlineThickness(3);
	Utils::SetOrigin(text2, Origins::MC);

	text3.setFont(font);
	text3.setLetterSpacing(0.2);
	text3.setCharacterSize(accentTextSize);
	text3.setFillColor(sf::Color::Yellow);
	text3.setOutlineColor(sf::Color::Black);
	text3.setOutlineThickness(3);
	Utils::SetOrigin(text3, Origins::MC);

	body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
	body.setScale(1, 1);
	body.setOrigin(body.getGlobalBounds().width * 0.5f, body.getGlobalBounds().height * 0.5f);
	Utils::SetOrigin(body, Origins::MC);
	body.setPosition({ 1920 * 0.5f, 1080 * 0.5f });

	text1.setPosition({ 1920 * 0.5f, 1080 * 0.5f });
}

void TutoUi::Update(float dt)
{
	soundTrigger1 += dt;
	soundTrigger2 += dt;
	soundTrigger3 += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		tutoIndex = 0;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		++tutoIndex;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		--tutoIndex;
	}
	if (tutoIndex < 0)
	{
		tutoIndex = 0;
	}

	if (tutoIndex == 0)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"캐릭터 조작키는 방향키 " + text2.getString() + L" 와 " + text3.getString() + L" 입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 1)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_9.png"));
		text1.setString(L"게임 내에서 V키를 누르면 화면을 가리고 할 수 있습니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 2)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"트랙은 총 3개가 있으며 플레이어가 어떤 트랙에 위치했는지 따라서 [도,레,미] 소리가 나옵니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 3)
	{
		sound.stop();
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"플레이어 위치 사운드는 5초마다 한번씩 재생됩니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		soundTrigger1 = 5.f;
	}
	if (tutoIndex == 4)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_2.png"));
		text1.setString(L"플레이어가 왼쪽에 위치했을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (soundTrigger1 > soundDelay)
		{
			sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/left.wav"));
			sound.setPitch(1.f);
			sound.setVolume(5.f);
			sound.play();
			soundTrigger1 = 0.f;
			soundTrigger2 = 5.f;
			soundTrigger3 = 5.f;
		}
	}
	if (tutoIndex == 5)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_3.png"));
		text1.setString(L"플레이어가 가운데에 위치했을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (soundTrigger2 > soundDelay)
		{
			sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/mid.wav"));
			sound.setPitch(1.f);
			sound.setVolume(5.f);
			sound.play();

			soundTrigger2 = 0.f;
			soundTrigger1 = 5.f;
			soundTrigger3 = 5.f;
		}
	}
	if (tutoIndex == 6)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_4.png"));
		text1.setString(L"플레이어가 오른쪽에 위치했을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (soundTrigger3 > soundDelay)
		{
			sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/right.wav"));
			sound.setPitch(1.f);
			sound.setVolume(5.f);
			sound.play();
			soundTrigger3 = 0.f;
			soundTrigger1 = 5.f;
			soundTrigger2 = 5.f;
		}
	}
	if (tutoIndex == 7)
	{
		soundTrigger3 = 5.f;
		sound.stop();
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"    적은 3종류가 있습니다. 적들은 나오는 트랙이 정해져있습니다. \n 적이 나올 때는 소리가 나기시작하고, 가까울 수록 소리가 커집니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		bassPlay = true;
	}
	if (tutoIndex == 8)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_5.png"));
		text1.setString(L"적이 왼쪽에서 나왔을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (bassPlay == true)
		{
			PlayBass();
			bassPlay = false;
			drumPlay = true;
			castanetsPlay = true;
		}
	}
	if (tutoIndex == 9)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_6.png"));
		text1.setString(L"적이 가운데에서 나왔을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (drumPlay == true)
		{
			PlayDrum();
			bassPlay = true;
			drumPlay = false;
			castanetsPlay = true;
		}
	}
	if (tutoIndex == 10)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_7.png"));
		text1.setString(L"적이 오른쪽에서 나왔을 때의 소리입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (castanetsPlay == true)
		{
			PlayCastanets();
			bassPlay = true;
			drumPlay = true;
			castanetsPlay = false;
		}
	}
	if (tutoIndex == 11)
	{
		castanetsPlay = true;
		sound.stop();
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_8.png"));
		text1.setString(L"적은 동시에 두마리가 나올 수 있습니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		soundTrigger1 = 5.f;
	}
	if (tutoIndex == 12)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"적과 부딪히지 않고, 적이 지나가면 스코어가 올라가며 소리가 나옵니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (soundTrigger1 > soundDelay)
		{
			sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/scoreup.wav"));
			sound.setPitch(1);
			sound.setVolume(5.f);
			sound.play();
			soundTrigger1 = 0.f;
			soundTrigger2 = 5.f;
			soundTrigger3 = 0.f;
		}
		if (soundTrigger3 > soundDelay * 0.5f)
		{
			sound.stop();
		}
	}
	if (tutoIndex == 13)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"적과 부딪힌다면 라이프가 감소되고, 사운드가 나옵니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
		if (soundTrigger2 > soundDelay)
		{
			sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/damage.wav"));
			sound.setPitch(1);
			sound.setVolume(5.f);
			sound.play();
			soundTrigger2 = 0.f;
			soundTrigger1 = 5.f;
			soundTrigger3 = 0.f;
		}
		if (soundTrigger3 > soundDelay * 0.5f)
		{
			sound.stop();
		}
	}
	if (tutoIndex == 14)
	{
		soundTrigger2 = 5.f;
		sound.stop();
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"라이프가 0이 되면 게임오버됩니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 15)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"라이프는 총 3개가 있고, 스코어를 일정량 올리면 1이 추가 됩니다. 하지만 최대 라이프는 3입니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 16)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_10.png"));
		text1.setString(L"게임 오버가 되었을 때 Enter를 누르면 타이틀 화면으로 돌아갑니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 17)
	{
		text2.setString("Left");
		text3.setString("Right");
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text1.setString(L"튜토리얼이 끝났습니다. 한번 더 누르시면 타이틀 화면으로 돌아갑니다.");
		text1.setOrigin(text1.getGlobalBounds().width * 0.5f, text1.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 18)
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		tutoIndex = 0;
	}
}

void TutoUi::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(text1);
}

void TutoUi::PlayBass()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/bass.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(25.f);
	sound.play();
}

void TutoUi::PlayDrum()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/drum.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(25.f);
	sound.play();
}

void TutoUi::PlayCastanets()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/castanets.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(25.f);
	sound.play();
}
