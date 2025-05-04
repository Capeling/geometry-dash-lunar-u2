#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementManager.hpp>

class $modify(HookedAchievementManager, AchievementManager) {
public:
    $override
    void addManualAchievements();
};