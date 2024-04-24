#include "../headers/HookedGameLevelManager.h"

GJGameLevel* HookedGameLevelManager::getMainLevel(int levelID, bool _isLoaded) {
    auto level = GameLevelManager::getMainLevel(levelID, _isLoaded);

    switch(levelID) {
        default:
            level->m_creatorName = "GenaMorphosis";
            level->m_accountID = 10026833;
            break;
        case 8:
            level->m_creatorName = "Andrexel";
            level->m_accountID = 8327873;
            break;
        case 9:
            level->m_creatorName = "RealToastGD";
            level->m_accountID = 26666582;
            break;
    }
    return level;
}