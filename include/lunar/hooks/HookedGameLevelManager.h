#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

class $modify(HookedGameLevelManager, GameLevelManager) {
public:
    $override
    GJGameLevel* getMainLevel(int, bool);
};