#include <hooks/HookedGameStatsManager.h>

using namespace geode::prelude;

int HookedGameStatsManager::getBaseCurrencyForLevel(GJGameLevel* level) {
    if(level->m_levelID.value() == 10) {
        return 400;
    }
    return GameStatsManager::getBaseCurrencyForLevel(level);
}

void HookedGameStatsManager::checkCoinAchievement(GJGameLevel* level) {

    auto GM = GameManager::sharedState();

    int coinPercent = (getCollectedCoinsForLevel(level) / 3.f) * 100.f;
    auto achievementID = fmt::format("geometry.ach.lunar.levelcoin{:02}", level->m_levelID.value());

    if(level->m_levelType == GJLevelType::Local) {
        GM->reportAchievementWithID(achievementID.c_str(), coinPercent, false);
    }
    //static_cast<HookedGameManager*>(GameManager::sharedState())->checkForUltAch();
}