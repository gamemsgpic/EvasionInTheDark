#include "stdafx.h"
#include "SaveData.h"

SaveData* SaveDataV1::VersionUp()
{
    SaveDataV2* newData = new SaveDataV2();
    newData->easyHighscore = easyHighscore;
    newData->normalHighscore = normalHighscore;
    //newData->gold
    return newData;
}
