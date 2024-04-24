#pragma once
#include "../../defs/all.h"
#include <Geode/modify/LevelPage.hpp>

class $modify(HookedLevelPage, LevelPage) {

    $override
    void onTheTower(CCObject* sender);

    $override
    void updateDynamicPage(GJGameLevel* level);

    $override
    void onInfo(CCObject* sender);

    $override
    void onPlay(CCObject* sender);

    cocos2d::CCArray* getFirstDialogArray();
};