#include "../headers/HookedLevelPage.h"
#include "../../utils/WorkingDialogObject.h"
#include "../../layers/headers/VaultLayer.h"

void HookedLevelPage::onTheTower(CCObject* sender) {
    CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, VaultLayer::scene()));
    return;
    //return LevelPage::onTheTower(sender);
    #ifndef GEODE_IS_ANDROID
    auto dl = DialogLayer::createDialogLayer(nullptr, getDialogArray(), 2);
    dl->animateIn(DialogAnimationType::FromRight);
    CCScene::get()->addChild(dl);
    #endif
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

CCArray* HookedLevelPage::getDialogArray() {
    CCArray* array = CCArray::create();

    array->addObject(WorkingDialogObject::create("Scratch", "<cr><s160>HEY!</s></c> <d030>Hold on.", 11, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("Scratch", "It's too early for you to see <cl>him</c>.", 13, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("Scratch", "Check <cl>him</c> out later, <d040>he's not in the mood <cg>right now.<d030>.<d030>.</c>", 12, 1, false, {255, 255, 255}));
    
    return array;
}