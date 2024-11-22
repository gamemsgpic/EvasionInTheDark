#pragma once
namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y)
}

struct SaveData
{
public:
	int version = 0;
	int easyHighscore = 0;
	int normalHighscore = 0;
	int extremeHighscore = 0;
	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{
public:
	SaveDataV1() { version = 1; }

	SaveData* VersionUp() override;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, version, easyHighscore, normalHighscore, extremeHighscore)
};

struct SaveDataV2 : public SaveData
{
	SaveDataV2() { version = 2; }

	SaveData* VersionUp() override { return nullptr; }

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version, easyHighscore, normalHighscore, extremeHighscore)
};

typedef SaveDataV2 SaveDataVC;
