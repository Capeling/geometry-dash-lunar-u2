#pragma once
#include "../../defs/all.h"
#include <Geode/modify/AchievementManager.hpp>

class $modify(HookedAchievementManager, AchievementManager) {
public:
    $override
    void addManualAchievements();

    $override
    void reportAchievementWithID(char const* p0, int p1, bool p2);

    //$override
    //CCDictionary* addAchievement(gd::string achID, gd::string title, gd::string descUnlock, gd::string descLock, gd::string reward, int idk);
};