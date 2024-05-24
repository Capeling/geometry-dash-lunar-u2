#pragma once
#include "../../defs/all.h"
#include <Geode/modify/GameManager.hpp>

class $modify(HookedGameManager, GameManager) {
    gd::string sheetNameForIcon(int iconID, int iconType);
    CCTexture2D* loadIcon(int iconID, int iconType, int _idk);

    void reportPercentageForLevel(int levelID, int percent, bool isPractice);
    void dataLoaded(DS_Dictionary*);
    void checkForUltAch();
};