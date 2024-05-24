#include "../headers/HookedMenuLayer.h"
#include "../../utils/WorkingDialogObject.h"
#include "../../layers/headers/CreditsLayer.h"
#include "../../nodes/headers/SavePopup.h"
#include "../headers/HookedGameManager.h"

bool HookedMenuLayer::init() {
    if(!MenuLayer::init())
        return false;
    
    auto mainTitle = getChildByID("main-title");
    
    if(mainTitle) {
        auto lunarTitle = CCSprite::createWithSpriteFrameName("GJL_lunarLogo_001.png"_spr);
        lunarTitle->setPosition({334, -20});
        mainTitle->addChild(lunarTitle);
    }

    auto moreGamesBtn = static_cast<CCMenuItemSpriteExtra*>(getChildByID("more-games-menu")->getChildByID("more-games-button"));
    if(moreGamesBtn) {
        moreGamesBtn->setNormalImage(CCSprite::createWithSpriteFrameName("GJL_creditsBtn_001.png"_spr));
    }

    bool hasSeenSaveWarning = GameManager::get()->getUGV("50");
    if(!hasSeenSaveWarning) {
        auto popup = SavePopup::create();
        popup->m_scene = this;
        popup->show();
    }
    return true;
}

void HookedMenuLayer::onCreator(CCObject* sender) {
    //return MenuLayer::onCreator(sender);

    auto dl = DialogLayer::createDialogLayer(nullptr, getDialogArray(), 2);
    dl->animateIn(DialogAnimationType::FromLeft);
    CCScene::get()->addChild(dl);
}

void HookedMenuLayer::onMoreGames(CCObject*) {
    //auto alert = FLAlertLayer::create("Credits", "<cl>Mod Developer</c>: Capeling\n<cg>Levels (1-4)</c>: GenaMorphosis\n<cp>Icons</c>: FatzFries", "OK");
    //alert->show();
    CreditsLayer::create("Credits")->show();
}

void HookedMenuLayer::keyDown(enumKeyCodes keyCode) {
    MenuLayer::keyDown(keyCode);
}

CCArray* HookedMenuLayer::getDialogArray() {
    CCArray* array = CCArray::create();

    array->addObject(WorkingDialogObject::create("???", "You can't go there.", 52, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("???", "Leave <cl>Lunar</c>, <d040>and I will let you through<d020>.<d020>.<d020>.", 52, 1, false, {255, 255, 255}));
    
    return array;
}