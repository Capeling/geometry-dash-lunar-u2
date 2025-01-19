#include <hooks/HookedLevelPage.h>
#include <layers/VaultLayer.h>

using namespace geode::prelude;

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


    if(level->m_levelID == -2) {
        CCSpriteFrameCache* SFC = CCSpriteFrameCache::sharedSpriteFrameCache();

        CCMenu* towerMenu = getChildByType<CCMenu>(1);
        if(!towerMenu) return;
        CCMenuItemSpriteExtra* towerBtn = towerMenu->getChildByType<CCMenuItemSpriteExtra>(0);
        if(!towerBtn) return;

        CCSprite* towerSpr = static_cast<CCSprite*>(towerBtn->getNormalImage());
        if(!towerSpr) return;
        CCSprite* towerTextSpr = towerSpr->getChildByType<CCSprite>(0);
        if(!towerTextSpr) return;

        towerSpr->setDisplayFrame(SFC->spriteFrameByName("GJL_secretDoor_001.png"_spr));
        towerSpr->setScale(1.1);
        // towerSpr->setContentSize({99, 162});
        towerTextSpr->setVisible(false);

        for(int i = 0; i < 3; i++) {
            auto node = towerSpr->getChildByType<CCParticleSystemQuad>(i);
            if(!node) continue;
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

    array->addObject(DialogObject::create("???", "Huh? <d040>Who is this?", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", ".<d030>.<d030>.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "<cr>Nevermind</c>.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "No matter <cl>who</c> you are, <d040>I'm <cr>not</c> interested.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "If you want to have a real conversation with me, <d040>bring me something with <cy>gold</c>.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "Ingots, <d030><cy>coins</c>, <d030>rings, <d030>I don't care.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "It should be <cy>GOLD</c>, <d030>and there will be <cl>20</c> of it.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "Now go away!", 55, 1, false, {255, 255, 255}));
    
    return array;
}

CCArray* HookedLevelPage::getNotEnoughDialogArray() {

    auto GSM = GameStatsManager::sharedState();

    CCArray* array = CCArray::create();
    
    int coins = GSM->getStat("8");

    if(coins < 4) {
        array->addObject(DialogObject::create("???", fmt::format("<cy><s100>{}</s></c>?!", coins).c_str(), 55, 1, false, {255, 255, 255}));
    } else {
    array->addObject(DialogObject::create("???", fmt::format("1, <d040>2, <d040>3.<d020>.<d020>. <d040><cy><s100>{}</s></c>?!", coins).c_str(), 55, 1, false, {255, 255, 255}));
    }
    array->addObject(DialogObject::create("???", "<s100>Can you not read?!</s> <d080>I said <cl>20</c>!", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "Go away!", 55, 1, false, {255, 255, 255}));
    
    return array;
}