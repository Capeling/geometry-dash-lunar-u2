#include "../../defs/all.h"
#include <Geode/modify/GameStatsManager.hpp>

class $modify(HookedGameStatsManager, GameStatsManager) {
    int getBaseCurrency(int, bool, int);

    void checkCoinAchievement(GJGameLevel*);
};