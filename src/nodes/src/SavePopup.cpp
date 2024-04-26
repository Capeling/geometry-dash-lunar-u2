#include "../headers/SavePopup.h"

SavePopup* SavePopup::create() {
    auto ret = new SavePopup();
    if(ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool SavePopup::init() {
    if(!FLAlertLayer::init(150))
        return false;

    auto director = CCDirector::get();
    auto winSize = director->getWinSize();

    m_noElasticity = true;
    m_reverseKeyBack = true;

    m_background = CCScale9Sprite::create("GJ_square01.png");
    m_background->setContentSize({350.f, 200.f});
    m_background->setPosition(winSize / 2);

    m_mainLayer->addChild(m_background, -2);

    m_darkenedArea = CCScale9Sprite::create("GJ_square01.png");
    m_darkenedArea->setContentSize({320.f, 100.f});
    m_darkenedArea->setPosition(winSize.width / 2, winSize.height / 2 + 6);
    m_darkenedArea->setColor({0, 0, 0});
    m_darkenedArea->setOpacity(60);

    m_mainLayer->addChild(m_darkenedArea, -1);

    m_title = CCLabelBMFont::create("Save Notice", "goldFont.fnt");
    m_title->setPosition(winSize.width / 2, m_background->getPositionY() + 100.f - 16.f); // idk
    m_title->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    m_title->setScale(0.8);

    m_mainLayer->addChild(m_title);

    m_textArea = TextArea::create("<cl>Lunar</c> uses a different save file,\nall save data <cl>will be restored</c>\nwhen you turn off the mod.", "bigFont.fnt", 1.f, 1000.f, {0.5, 1.F}, 42.f, false);
    m_textArea->setPosition({winSize.width / 2, winSize.height / 2 + 15.f});
    m_textArea->setScale(0.5f);

    m_buttonMenu = CCMenu::create();

    m_mainLayer->addChild(m_buttonMenu);


    m_button1 = ButtonSprite::create("OK",0,0,1.0,false,"goldFont.fnt","GJ_button_01.png",0.0);
    m_okBtn = CCMenuItemSpriteExtra::create(m_button1, this, menu_selector(SavePopup::onClose));
    m_okBtn->setPosition(m_buttonMenu->convertToNodeSpace({winSize.width / 2, m_background->getPositionY() - 100.f + 25.f}));

    m_buttonMenu->addChild(m_okBtn);

    m_mainLayer->addChild(m_textArea);


    return true;
}

void SavePopup::onClose(CCObject*) {
    GameManager::get()->setUGV("50", true);
    setKeypadEnabled(false);
    setTouchEnabled(false);
    removeFromParentAndCleanup(true);
}

void SavePopup::keyBackClicked() {
    return;
}