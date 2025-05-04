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

    // $override
    // void onPlay(CCObject*);

    #ifdef DEBUG_BUILD
    $override
    virtual void keyDown(cocos2d::enumKeyCodes);
    #endif

    cocos2d::CCArray* getDialogArray();
};