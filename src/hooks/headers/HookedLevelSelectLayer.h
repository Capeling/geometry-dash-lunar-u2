#pragma once
#include "../../defs/all.h"
#include <Geode/modify/LevelSelectLayer.hpp>

class $modify(HookedLevelSelectLayer, LevelSelectLayer) {
public:
    $override
    bool init(int pageID);

    $override
    ccColor3B colorForPage(int pageID);

    $override
    void onPrev(CCObject* sender);
};