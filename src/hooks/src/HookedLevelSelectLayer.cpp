#include "../headers/HookedLevelSelectLayer.h"

bool HookedLevelSelectLayer::init(int pageID) {
    return LevelSelectLayer::init(pageID);
}

ccColor3B HookedLevelSelectLayer::colorForPage(int pageID) {
    auto GM = GameManager::sharedState();
    //5, 7, 8, 9, 10, 11, 1, 3, 4, 5, 94, 8
	int colIDs[12] = { 5, 7, 8, 9, 10, 11, 1, 3, 4, 5, 94, 8 };
    if(colIDs[pageID % 12] == 94)
        return {37, 44, 52}; // The Tower

    return GM->colorForIdx(colIDs[pageID % 12]);
    
    //return LevelSelectLayer::colorForPage(pageID);
}

void HookedLevelSelectLayer::onPrev(CCObject* sender) {
    LevelSelectLayer::onPrev(sender);
}