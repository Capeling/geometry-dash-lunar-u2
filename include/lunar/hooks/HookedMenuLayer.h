#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

class $modify(HookedMenuLayer, MenuLayer) {
    $override
    bool init();

    $override
    void onCreator(CCObject*);

    $override
    void onMoreGames(CCObject*);

    $override
    virtual void keyDown(cocos2d::enumKeyCodes);

    cocos2d::CCArray* getDialogArray();
};