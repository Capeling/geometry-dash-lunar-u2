#include "../headers/HookedLevelPage.h"
#include "../../utils/WorkingDialogObject.h"
#include "../../layers/headers/VaultLayer.h"

void HookedLevelPage::onTheTower(CCObject* sender) {

    auto GSM = GameStatsManager::sharedState();
    auto GM = GameManager::sharedState();

    if(GSM->getStat("8") <= 19) {
        if(!GM->getUGV("51")) {
            auto dl = DialogLayer::createDialogLayer(nullptr, getFirstDialogArray(), 4);
            dl->animateInRandomSide();
            CCScene::get()->addChild(dl);
            GM->setUGV("51", true);
            return;
        }

        auto dl = DialogLayer::createDialogLayer(nullptr, getNotEnoughDialogArray(), 4);
        dl->animateInRandomSide();
        CCScene::get()->addChild(dl);
        return;
    }

    CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, VaultLayer::scene()));
}

void HookedLevelPage::updateDynamicPage(GJGameLevel* level) {
    LevelPage::updateDynamicPage(level);

    CCSpriteFrameCache* SFC = CCSpriteFrameCache::sharedSpriteFrameCache();

    if(level->m_levelID == -2) {
        CCMenu* towerMenu = getChildOfType<CCMenu>(this, 1);
        CCMenuItemSpriteExtra* towerBtn = getChildOfType<CCMenuItemSpriteExtra>(towerMenu, 0);

        CCSprite* towerSpr = getChildOfType<CCSprite>(towerBtn, 0);
        CCSprite* towerTextSpr = getChildOfType<CCSprite>(towerSpr, 0);

        towerSpr->setDisplayFrame(SFC->spriteFrameByName("GJL_secretDoor_001.png"_spr));
        towerSpr->setScale(1.1);
        //towerSpr->setContentSize({99, 162});
        towerTextSpr->setVisible(false);

        for(int i = 0; i < 3; i++) {
            auto node = getChildOfType<CCParticleSystemQuad>(towerSpr, i);
            //node->setPosition(ccp(node->getPositionX() - 1, node->getPositionY() + 7));
            node->setPosition(towerSpr->getScaledContentSize() / 2.2);
        }
    }
}

void HookedLevelPage::onInfo(CCObject* sender) {
    if(m_level->m_levelID.value() == -2) {
        
        return FLAlertLayer::create(nullptr, "The Vault", "The path leads to an <cr>old vault</c>. It's been left alone for <cg>years</c>, but still someone <co>lives</c> there.", "OK", nullptr, 360)->show();
    }
    LevelPage::onInfo(sender);
}

void HookedLevelPage::onPlay(CCObject* sender) {
    return LevelPage::onPlay(sender);
}

CCArray* HookedLevelPage::getFirstDialogArray() {
    CCArray* array = CCArray::create();

    array->addObject(WorkingDialogObject::create("???", "Huh? <d040>Who is this?", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", ".<d030>.<d030>.", 204, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "<cr>Nevermind</c>.", 204, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "No matter <cl>who</c> you are, <d040>I'm <cr>not</c> interested.", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "If you want to have a real conversation with me, <d040>bring me something with <cy>gold</c>.", 54, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "Ingots, <d030><cy>coins</c>, <d030>rings, <d030>I don't care.", 204, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "It should be <cy>GOLD</c>, <d030>and it should be <cl>20</c> of it.", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "Now go away!", 52, 1, false, {255, 255, 255}));
    
    return array;
}

CCArray* HookedLevelPage::getNotEnoughDialogArray() {

    auto GSM = GameStatsManager::sharedState();

    CCArray* array = CCArray::create();
    
    int coins = GSM->getStat("8");

    if(coins < 4) {
        array->addObject(WorkingDialogObject::create("???", fmt::format("<cy><s100>{}</s></c>?!", coins).c_str(), 52, 1, false, {255, 255, 255}));
    } else {
    array->addObject(WorkingDialogObject::create("???", fmt::format("1, <d040>2, <d040>3.<d020>.<d020>. <d040><cy><s100>{}</s></c>?!", coins).c_str(), 52, 1, false, {255, 255, 255}));
    }
    array->addObject(WorkingDialogObject::create("???", "<s100>Can you not read?!</s> <d080>I said <cl>20</c>!", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "Go away!", 52, 1, false, {255, 255, 255}));
    
    return array;
}