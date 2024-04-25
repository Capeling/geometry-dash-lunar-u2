#include "../headers/HookedMenuLayer.h"
#include "../../utils/WorkingDialogObject.h"
#include "../../layers/headers/CreditsLayer.h"

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

    bool hasSeenSaveWarning = Mod::get()->getSavedValue<bool>("seen-saved-warning");
    if(!hasSeenSaveWarning) {
        auto alert = FLAlertLayer::create("Save Warning", "<cl>Geometry Dash: Lunar</c> uses a <co>different</c> save file to avoid <cr>stat modification</c>.\nYour <cg>save file</c> has not been <cr>deleted</c>, if you want to go back to your <cg>default</c> save file disable <cl>Geometry Dash: Lunar</c>.", "OK");
        alert->m_noElasticity = true;
        alert->m_scene = this;
        alert->show();
        Mod::get()->setSavedValue<bool>("seen-saved-warning", true);
    }
    return true;
}

void HookedMenuLayer::onCreator(CCObject* sender) {
    return MenuLayer::onCreator(sender);

    auto dl = DialogLayer::createDialogLayer(nullptr, getDialogArray(), 2);
    dl->animateIn(DialogAnimationType::FromLeft);
    CCScene::get()->addChild(dl);
}

void HookedMenuLayer::onMoreGames(CCObject*) {
    //auto alert = FLAlertLayer::create("Credits", "<cl>Mod Developer</c>: Capeling\n<cg>Levels (1-4)</c>: GenaMorphosis\n<cp>Icons</c>: FatzFries", "OK");
    //alert->show();
    CreditsLayer::create("Credits")->show();
}

CCArray* HookedMenuLayer::getDialogArray() {
    CCArray* array = CCArray::create();

    array->addObject(WorkingDialogObject::create("Scratch", "<cr><s190>STOP!</s></c> <d040><cl>He</c> will notice that.", 14, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("Scratch", "Its too <cr>risky</c>, <d020>you can't go right now.", 8, 1, false, {255, 255, 255}));
    array->addObject(WorkingDialogObject::create("Scratch", "Leave <cl>Lunar</c>, <d030>and I will let you <cg>through.<d030>.<d030>.</c>", 12, 1, false, {255, 255, 255}));
    
    return array;
}