#include <hooks/HookedLevelSelectLayer.h>

using namespace geode::prelude;

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

    m_scrollLayer->m_dynamicObjects->removeAllObjects();

    auto dotsArray = CCArrayExt<CCSprite*>(m_scrollLayer->m_dots);

    for(CCSprite* dot : dotsArray) {
        dot->removeFromParent();
    }

    m_scrollLayer->m_dots->removeAllObjects();

    for(int i = 1; i < 11; i++) {
        m_scrollLayer->m_dynamicObjects->addObject(GameLevelManager::get()->getMainLevel(i, true));
    }
    auto towerLevel = GJGameLevel::create();
    towerLevel->m_levelID = -2;
    auto comingSoon = GJGameLevel::create();
    comingSoon->m_levelID = -1;

    m_scrollLayer->m_dynamicObjects->addObject(towerLevel);
    m_scrollLayer->m_dynamicObjects->addObject(comingSoon);

    auto batchNode = CCSpriteBatchNode::create("smallDot.png", 29);
    m_scrollLayer->addChild(batchNode, 5);

    for(int i = 0; i < m_scrollLayer->m_dynamicObjects->count(); i++) {
        auto sprite = CCSprite::create("smallDot.png");
        batchNode->addChild(sprite);
        m_scrollLayer->m_dots->addObject(sprite);
    }

    m_scrollLayer->updateDots(0.f);
    m_scrollLayer->updatePages();
    this->updatePageWithObject(m_scrollLayer->m_pages->objectAtIndex(pageID % 3), m_scrollLayer->m_dynamicObjects->objectAtIndex(pageID));
    this->m_scrollLayer->repositionPagesLooped();

    return true;
}

ccColor3B HookedLevelSelectLayer::colorForPage(int pageID) {
    int count = m_scrollLayer->m_dynamicObjects->count();
    int page = (count + (pageID % count)) % count;

    auto GM = GameManager::sharedState();
    //5, 7, 8, 9, 10, 11, 1, 3, 4, 5, 94, 8
	int colIDs[12] = { 5, 7, 8, 9, 10, 11, 1, 3, 4, 5, 94, 8 };
    if(colIDs[page % 12] == 94)
        return {37, 44, 52}; // The Tower

    return GM->colorForIdx(colIDs[page % 12]);
    
    //return LevelSelectLayer::colorForPage(pageID);
}

CCArray* HookedLevelSelectLayer::getGoldCoinDialog() {
    CCArray* array = CCArray::create();

    array->addObject(DialogObject::create("???", "Huh, <d040>you actually did it.<d020>.<d020>.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "You got the <cy>gold</c> stuff.<d020>.<d020>.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "I didn't think <cl>you</c> could do it.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "The vault is open, <d040>remember though, <d040><cr>don't go looking at things you shouldn't be.</c><d020>.<d020>.", 55, 1, false, {255, 255, 255}));
    
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