#pragma once
#include "../../defs/all.h"
#include <Geode/modify/MenuLayer.hpp>

class $modify(HookedMenuLayer, MenuLayer) {
    $override
    bool init();

    $override
    void onCreator(CCObject*);

    $override
    void onMoreGames(CCObject*);

    CCArray* getDialogArray();
};