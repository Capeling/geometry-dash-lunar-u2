#include "../headers/HookedLevelSelectLayer.h"
#include "../../utils/WorkingDialogObject.h"

bool HookedLevelSelectLayer::init(int pageID) {
    if(!LevelSelectLayer::init(pageID))
        return false;
    
    auto GSM = GameStatsManager::sharedState();
    auto GM = GameManager::sharedState();

    if(GSM->getStat("8") >= 20 && !GM->getUGV("52")) {
        auto delay = CCDelayTime::create(0.4f);
        auto func = CCCallFunc::create(this, callfunc_selector(HookedLevelSelectLayer::createGoldCoinDialog));
        this->runAction(CCSequence::create(delay, func, 0));
    }

    return true;
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

CCArray* HookedLevelSelectLayer::getGoldCoinDialog() {
    CCArray* array = CCArray::create();

    array->addObject(WorkingDialogObject::create("???", "Huh, <d040>you actually did it.<d020>.<d020>.", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "You got the <cy>gold</c> stuff.<d020>.<d020>.", 204, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "I didn't think <cl>you</c> could do it.", 204, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "The vault is open, <d040>remember though, <d040><cr>don't go looking at things you shouldn't be.</c><d020>.<d020>.", 52, 1, false, {255, 255, 255}));
    
    return array;
}

void HookedLevelSelectLayer::createGoldCoinDialog() {
    auto dl = DialogLayer::createDialogLayer(nullptr, getGoldCoinDialog(), 4);
    dl->setZOrder(9999);
    dl->animateInRandomSide();
    this->addChild(dl);
    GameManager::get()->setUGV("52", true);
}

void HookedLevelSelectLayer::onPrev(CCObject* sender) {
    LevelSelectLayer::onPrev(sender);
}