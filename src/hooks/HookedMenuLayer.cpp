#include <hooks/HookedMenuLayer.h>
#include <layers/CreditsLayer.h>
#include <layers/VaultLayer.h>
#include <nodes/SavePopup.h>

using namespace geode::prelude;

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
    #ifndef DEBUG_ENABLED
    auto dl = DialogLayer::createDialogLayer(nullptr, getDialogArray(), 2);
    dl->animateInRandomSide();
    CCScene::get()->addChild(dl);
    #else
    MenuLayer::onCreator(sender);
    #endif
}

void HookedMenuLayer::onMoreGames(CCObject*) {
    //auto alert = FLAlertLayer::create("Credits", "<cl>Mod Developer</c>: Capeling\n<cg>Levels (1-4)</c>: GenaMorphosis\n<cp>Icons</c>: FatzFries", "OK");
    //alert->show();
    CreditsLayer::create()->show();
}

// void HookedMenuLayer::onPlay(CCObject*) {
//     CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, LunarSelectLayer::scene(0)));
// }

#ifdef DEBUG_ENABLED
void HookedMenuLayer::keyDown(enumKeyCodes keyCode) {
    if(keyCode == enumKeyCodes::KEY_T) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, VaultLayer::scene()));
    }
    MenuLayer::keyDown(keyCode);
}
#endif

CCArray* HookedMenuLayer::getDialogArray() {
    CCArray* array = CCArray::create();

    array->addObject(DialogObject::create("???", "You can't go there.", 55, 1, false, {255, 255, 255}));
    array->addObject(DialogObject::create("???", "Leave <cl>Lunar</c>, <d040>and I will let you through<d020>.<d020>.<d020>.", 55, 1, false, {255, 255, 255}));
    
    return array;
}