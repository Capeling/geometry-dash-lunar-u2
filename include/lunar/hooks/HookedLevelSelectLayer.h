#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

class $modify(HookedLevelSelectLayer, LevelSelectLayer) {
public:
    $override
    bool init(int pageID);

    $override
    cocos2d::ccColor3B colorForPage(int pageID);

    $override
    void onPrev(CCObject* sender);

    cocos2d::CCArray* getGoldCoinDialog();

    void createGoldCoinDialog();
};