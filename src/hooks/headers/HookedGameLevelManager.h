#pragma once
#include "../../defs/all.h"
#include <Geode/modify/GameLevelManager.hpp>

class $modify(HookedGameLevelManager, GameLevelManager) {
public:
    $override
    GJGameLevel* getMainLevel(int, bool);
};