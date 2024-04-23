#pragma once
#include "../../defs/all.h"
#include <Geode/modify/AchievementManager.hpp>

class $modify(HookedAchievementManager, AchievementManager) {
public:
    $override
    void addManualAchievements();
};