#include "../headers/HookedGameStatsManager.h"
#include "../headers/HookedGameManager.h"

int HookedGameStatsManager::getBaseCurrency(int p0, bool p1, int levelID) {
    if(levelID == 10) {
        return 400;
    }
    return GameStatsManager::getBaseCurrency(p0, p1, levelID);
}

void HookedGameStatsManager::checkCoinAchievement(GJGameLevel* level) {

    auto GM = GameManager::sharedState();

    int coinPercent = (getCollectedCoinsForLevel(level) / 3.f) * 100.f;
    auto achievementID = fmt::format("geometry.ach.lunar.levelcoin{:02}", level->m_levelID.value());

    log::info("coinPercent: {}, achID: {}", coinPercent, achievementID);


    if(level->m_levelType == GJLevelType::Local) {
        GM->reportAchievementWithID(achievementID.c_str(), coinPercent, false);
    }
    //static_cast<HookedGameManager*>(GameManager::sharedState())->checkForUltAch();
}