#include "../headers/HookedGameStatsManager.h"

int HookedGameStatsManager::getBaseCurrency(int p0, bool p1, int levelID) {
    if(levelID == 10) {
        return 400;
    }
    return GameStatsManager::getBaseCurrency(p0, p1, levelID);
}

void HookedGameStatsManager::checkCoinAchievement(GJGameLevel* level) {

    auto GM = GameManager::sharedState();

    if(level->m_levelType == GJLevelType::Local) {
        if(level->m_levelID.value() == 10) {
            GM->reportAchievementWithID("geometry.ach.lunar.demoncoin01", (getCollectedCoinsForLevel(level) / 3.f) * 100.f, false);
        }
        
    }
}