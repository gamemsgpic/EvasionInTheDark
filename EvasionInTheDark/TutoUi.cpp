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
	SoundMgr::Instance().SetBgmVolume(4.f);
	SoundMgr::Instance().PlayBgm("sound/bgm.wav");

	float textSize = 40.f;
	float accentTextSize = 43.f;
	sf::Font& font = FONT_MGR.Get("fonts/TmoneyRoundWindExtraBold.ttf");
	text.setFont(font);
	text.setLetterSpacing(0.2);
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3);
	Utils::SetOrigin(text, Origins::MC);

	body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
	body.setScale(1, 1);
	body.setOrigin(body.getGlobalBounds().width * 0.5f, body.getGlobalBounds().height * 0.5f);
	Utils::SetOrigin(body, Origins::MC);
	body.setPosition({ 1920 * 0.5f, 1080 * 0.5f });

	text.setPosition({ 1920 * 0.5f, 1080 * 0.5f });
	explainStart = 15.f;
	soundStartTrigger = 0.f;
}

void TutoUi::Update(float dt)
{
	explainStart += dt;
	soundTrigger1 += dt;
	soundTrigger2 += dt;
	soundTrigger3 += dt;
	soundStartTrigger += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		tutoIndex = 0;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		explainStart = 15.f;
		++tutoIndex;
		soundStartTrigger = 0.f;
		SoundMgr::Instance().StopAllSfx();
		sound.stop();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		explainStart = 15.f;
		--tutoIndex;
		soundStartTrigger = 0.f;
		SoundMgr::Instance().StopAllSfx();
		sound.stop();
	}
	if (tutoIndex < 0)
	{
		tutoIndex = 0;
	}
	if (tutoIndex == 0)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage0.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"        안녕하세요. 지금 계신곳은 튜토리얼 화면입니다.\n 방향키 왼쪽과 오른쪽으로 페이지를 전환 할 수 있습니다.\n           엔터를 누르시면 타이틀 화면으로 돌아갑니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}

	if (tutoIndex == 1)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage1.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"캐릭터 조작키는 방향키 왼쪽 그리고 오른쪽 입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 2)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage2.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_9.png"));
		text.setString(L"게임 내에서 V키를 누르면 화면을 가리고 할 수 있습니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 3)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage3.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"트랙은 총 3개가 있으며 플레이어가 어떤 트랙에 위치했는지 따라서 [도,레,미] 소리가 나옵니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 4)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage4.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"플레이어 위치 사운드는 5초마다 한번씩 재생됩니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		soundTrigger1 = 5.f;
	}
	if (tutoIndex == 5)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage5.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_2.png"));
		text.setString(L"플레이어가 왼쪽에 위치했을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (soundStartTrigger > soundStartDelay)
		{
			if (soundTrigger1 > soundDelay)
			{
				sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/left.wav"));
				sound.setPitch(1.f);
				sound.setVolume(10.f);
				sound.play();
				soundTrigger1 = 0.f;
				soundTrigger2 = 5.f;
				soundTrigger3 = 5.f;
			}
		}
	}
	if (tutoIndex == 6)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage6.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_3.png"));
		text.setString(L"플레이어가 가운데에 위치했을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (soundStartTrigger > soundStartDelay)
		{
			if (soundTrigger2 > soundDelay)
			{
				sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/mid.wav"));
				sound.setPitch(1.f);
				sound.setVolume(10.f);
				sound.play();

				soundTrigger2 = 0.f;
				soundTrigger1 = 5.f;
				soundTrigger3 = 5.f;
			}
		}
	}
	if (tutoIndex == 7)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage7.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_4.png"));
		text.setString(L"플레이어가 오른쪽에 위치했을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (soundStartTrigger > soundStartDelay)
		{
			if (soundTrigger3 > soundDelay)
			{
				sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/right.wav"));
				sound.setPitch(1.f);
				sound.setVolume(10.f);
				sound.play();
				soundTrigger3 = 0.f;
				soundTrigger1 = 5.f;
				soundTrigger2 = 5.f;
			}
		}
	}
	if (tutoIndex == 8)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage8.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;
		soundTrigger3 = 5.f;
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"    적은 3종류가 있습니다. 적들은 나오는 트랙이 정해져있습니다. \n 적이 나올 때는 소리가 나기시작하고, 가까울수록 소리가 커집니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		bassPlay = true;
	}
	if (tutoIndex == 9)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage9.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_5.png"));
		text.setString(L"적이 왼쪽에서 나왔을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (bassPlay == true)
		{
			if (soundStartTrigger > soundStartDelay - 0.5f)
			{
				PlayBass();
				bassPlay = false;
				drumPlay = true;
				castanetsPlay = true;
			}
		}
	}
	if (tutoIndex == 10)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage10.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_6.png"));
		text.setString(L"적이 가운데에서 나왔을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (drumPlay == true)
		{
			if (soundStartTrigger > soundStartDelay - 0.5f)
			{
				PlayDrum();
				bassPlay = true;
				drumPlay = false;
				castanetsPlay = true;
			}
		}
	}
	if (tutoIndex == 11)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage11.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_7.png"));
		text.setString(L"적이 오른쪽에서 나왔을 때의 소리입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);

		if (castanetsPlay == true)
		{
			if (soundStartTrigger > soundStartDelay - 0.5f)
			{
				PlayCastanets();
				bassPlay = true;
				drumPlay = true;
				castanetsPlay = false;
			}
		}
	}
	if (tutoIndex == 12)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage12.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;
		castanetsPlay = true;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_8.png"));
		text.setString(L"적은 동시에 두마리가 나올 수 있습니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		soundTrigger1 = 5.f;
	}
	if (tutoIndex == 13)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage13.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"적과 부딪히지 않고, 적이 지나가면 스코어가 올라가며 소리가 나옵니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (soundStartTrigger > soundStartDelay + 1.5f)
		{
			if (soundTrigger1 > soundDelay)
			{
				sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/scoreup.wav"));
				sound.setPitch(1);
				sound.setVolume(10.f);
				sound.play();
				soundTrigger1 = 0.f;
				soundTrigger2 = 5.f;
				soundTrigger3 = 0.f;
			}
		}
	}
	if (tutoIndex == 14)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage14.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"적과 부딪힌다면 라이프가 감소되고, 사운드가 나옵니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
		if (soundStartTrigger > soundStartDelay + 1.f)
		{
			if (soundTrigger2 > soundDelay)
			{
				sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/damage.wav"));
				sound.setPitch(1);
				sound.setVolume(10.f);
				sound.play();
				soundTrigger2 = 0.f;
				soundTrigger1 = 5.f;
				soundTrigger3 = 0.f;
			}
		}
	}
	if (tutoIndex == 15)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage15.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;
		soundTrigger2 = 5.f;

		sound.stop();
		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"라이프가 0이 되면 게임오버됩니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 16)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage16.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"라이프는 총 3개가 있고, 스코어를 일정량 올리면 1이 추가 됩니다. 하지만 최대 라이프는 3입니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 17)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage17.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_10.png"));
		text.setString(L"게임오버가 되었을 때 Enter를 누르면 타이틀 화면으로 돌아갑니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 18)
	{
		if (explainStart > explainEnd)
		{
			SoundMgr::Instance().CanStopPlaySfx(SOUNDBUFFER_MGR.Get("sound/tutopage18.wav"))->setVolume(20.f);
			explainStart = 0.f;
		}
		explainStart = 0.f;

		body.setTexture(TEXTURE_MGR.Get("graphics/Tuto_1.png"));
		text.setString(L"튜토리얼이 끝났습니다. 오른쪽키를 한번 더 누르시면 타이틀 화면으로 돌아갑니다.");
		text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
	}
	if (tutoIndex == 19)
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		tutoIndex = 0;
	}
}

void TutoUi::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(text);
}

void TutoUi::PlayBass()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/bass.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(50.f);
	sound.play();
}

void TutoUi::PlayDrum()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/drum.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(50.f);
	sound.play();
}

void TutoUi::PlayCastanets()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get("sound/castanets.wav"));
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(50.f);
	sound.play();
}