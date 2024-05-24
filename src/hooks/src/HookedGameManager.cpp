#include "../headers/HookedGameManager.h"

gd::string HookedGameManager::sheetNameForIcon(int iconID, int iconType) {
    return GameManager::sheetNameForIcon(iconID, iconType);
}
CCTexture2D* HookedGameManager::loadIcon(int iconID, int iconType, int _idk) {
    if(iconID == 2) {
        if(iconType == 1 || iconType == 2 || iconType == 3 || iconType == 7 || iconType == 8) {
            return nullptr;
        }
    }
    if(iconType == 6) {
        if(iconID == 2 || iconID == 3) {
            return nullptr;
        }
    }

    if(iconType == 0) {
        if(iconID < 31 && iconID > 12) {
            return nullptr;
        }
    }
    return GameManager::loadIcon(iconID, iconType, _idk);
}

void HookedGameManager::reportPercentageForLevel(int levelID, int percent, bool isPractice) {

    GameManager::reportPercentageForLevel(levelID, percent, isPractice);
    log::info("hi: {}, {}, {}", levelID, percent, isPractice);

    if(levelID == 10 && !isPractice && percent >= 60)
        GameManager::sharedState()->reportAchievementWithID("geometry.ach.lunar.percent01", 100, false);
}

void HookedGameManager::checkForUltAch() {
    auto GSM = GameStatsManager::sharedState();
    auto GLM = GameLevelManager::sharedState();

    int coinPercent1 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(1, false)) / 3.f) * 100.f;
    int coinPercent2 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(2, false)) / 3.f) * 100.f;
    int coinPercent3 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(3, false)) / 3.f) * 100.f;
    int coinPercent4 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(4, false)) / 3.f) * 100.f;
    int coinPercent5 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(5, false)) / 3.f) * 100.f;
    int coinPercent6 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(6, false)) / 3.f) * 100.f;
    int coinPercent7 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(7, false)) / 3.f) * 100.f;
    int coinPercent8 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(8, false)) / 3.f) * 100.f;
    int coinPercent9 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(9, false)) / 3.f) * 100.f;
    int coinPercent10 = (GSM->getCollectedCoinsForLevel(GLM->getMainLevel(10, false)) / 3.f) * 100.f;

    if(coinPercent1 + coinPercent2 + coinPercent3 + coinPercent4 + coinPercent5 + coinPercent6 + coinPercent7 + coinPercent8 + coinPercent9 + coinPercent10 == 1000) {
        GameManager::sharedState()->reportAchievementWithID("geometry.ach.lunar.ultimate", 100, false);
    }
}

void HookedGameManager::dataLoaded(DS_Dictionary* dict) {
    GameManager::dataLoaded(dict);
}