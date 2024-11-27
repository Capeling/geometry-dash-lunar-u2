#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>

class $modify(HookedGameStatsManager, GameStatsManager) {
    int getBaseCurrencyForLevel(GJGameLevel*);

    void checkCoinAchievement(GJGameLevel*);
};