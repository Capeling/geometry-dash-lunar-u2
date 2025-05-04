#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelPage.hpp>

class $modify(HookedLevelPage, LevelPage) {

    static void onModify(auto& self) {
        self.setHookPriorityPost("LevelPage::updateDynamicPage", geode::Priority::First);
    }

    $override
    void onTheTower(CCObject* sender);

    $override
    void updateDynamicPage(GJGameLevel* level);

    $override
    void onInfo(CCObject* sender);

    $override
    void onPlay(CCObject* sender);

    cocos2d::CCArray* getFirstDialogArray();

    cocos2d::CCArray* getNotEnoughDialogArray();
};