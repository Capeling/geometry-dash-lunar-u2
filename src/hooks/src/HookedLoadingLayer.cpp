#include "../headers/HookedLoadingLayer.h"

void HookedLoadingLayer::loadingFinished() {
    CCSpriteFrameCache::get()->addSpriteFramesWithFile("IconSheetGenerated.plist"_spr);

    auto GSM = GameStatsManager::sharedState();

    auto GLM = GameLevelManager::sharedState();
    
    GSM->checkCoinAchievement(GLM->getMainLevel(1, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(2, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(3, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(4, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(5, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(6, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(7, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(8, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(9, false));
    GSM->checkCoinAchievement(GLM->getMainLevel(10, false));
    
    LoadingLayer::loadingFinished();
}

bool HookedLoadingLayer::init(bool fromReload) {
    if(!LoadingLayer::init(fromReload))
        return false;
    auto SFC = CCSpriteFrameCache::get();

    auto director = CCDirector::get();
    auto winSize = director->getWinSize();
    auto GM = GameManager::sharedState();

    auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
    CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str()); 

    SFC->addSpriteFramesWithFile("LunarSheet.plist"_spr);

    auto mainTitle = getChildOfType<CCSprite>(this, 1);
    if(!mainTitle) return true;
    
    auto lunarTitle = CCSprite::createWithSpriteFrameName("GJL_lunarLogo_001.png"_spr);
    if(!lunarTitle) return true;
    lunarTitle->setPosition({334, -20});
    lunarTitle->setScale(1.1f);

    mainTitle->addChild(lunarTitle);
    mainTitle->setPositionY(mainTitle->getPositionY() + 22.f);

    CCSprite* robtopLogo = getChildOfType<CCSprite>(this, 2);
    if(!robtopLogo) return true;
    robtopLogo->setDisplayFrame(SFC->spriteFrameByName("GJ_genaLogo_001.png"_spr));
    robtopLogo->setPositionY(robtopLogo->getPositionY() + 22.f);

    robtopLogo->setScale(1.0f);

    if(!GM->getUGV("30")) {
        GM->setUGV("30", true);
    }

    return true;
}