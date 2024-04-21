#include "../headers/HookedGameStatsManager.h"

int HookedGameStatsManager::getBaseCurrency(int p0, bool p1, int levelID) {
    if(levelID == 10) {
        return 400;
    }
    return GameStatsManager::getBaseCurrency(p0, p1, levelID);
}