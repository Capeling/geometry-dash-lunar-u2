#pragma once
#include "../../defs/all.h"
#include <Geode/modify/GameManager.hpp>

class $modify(HookedGameManager, GameManager) {
    gd::string sheetNameForIcon(int iconID, int iconType);
    CCTexture2D* loadIcon(int iconID, int iconType, int _idk);

    $override
    void reportPercentageForLevel(int levelID, int percent, bool isPractice);

    $override
    void dataLoaded(DS_Dictionary*);

    $override
    void returnToLastScene(GJGameLevel*);

    void checkForUltAch();
};