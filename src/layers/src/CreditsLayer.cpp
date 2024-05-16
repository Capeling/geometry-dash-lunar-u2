#include "../headers/CreditsLayer.h"
#include "../../nodes/headers/CreditNode.h"
#include "../../nodes/headers/LevelNode.h"

bool CreditsLayer::setup(std::string const& title) {
    setID("credits-layer"_spr);

    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    m_creditsLayer = CCLayer::create();
    m_creditsLayer->setID("credits-tab"_spr);

    m_levelsLayer = CCLayer::create();
    m_levelsLayer->setID("levels-tab"_spr);

    m_debugLayer = CCLayer::create();
    m_debugLayer->setID("debug-tab"_spr);

    setupCreditsTab();
    setupLevelsTab();
    setupDebugTab();

    m_mainLayer->addChild(m_creditsLayer, 1);
    m_mainLayer->addChild(m_levelsLayer, 1);
    m_mainLayer->addChild(m_debugLayer, 1);

    auto forwardTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    forwardTabSpr->setFlipX(true);
    m_forwardTabBtn = CCMenuItemSpriteExtra::create(forwardTabSpr, this, menu_selector(CreditsLayer::onChangeTab));
    m_forwardTabBtn->setTag(1);

    m_forwardTabMenu = CCMenu::create();
    m_forwardTabMenu->setPosition(director->getScreenRight() - 25, winSize.height / 2);
    m_forwardTabMenu->addChild(m_forwardTabBtn);

    auto backTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    m_backTabBtn = CCMenuItemSpriteExtra::create(backTabSpr, this, menu_selector(CreditsLayer::onChangeTab));
    m_backTabBtn->setTag(-1);

    m_backTabMenu = CCMenu::create();
    m_backTabMenu->setPosition(director->getScreenLeft() + 25, winSize.height / 2);
    m_backTabMenu->addChild(m_backTabBtn);

    m_mainLayer->addChild(m_forwardTabMenu);
    m_mainLayer->addChild(m_backTabMenu);

    changeTab();

    return true;
}

void CreditsLayer::setupCreditsTab() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto creditsLabel = CCLabelBMFont::create("Credits", "bigFont.fnt");
    creditsLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight()));

    auto capeUser = CreditNode::create("Capeling", "Mod Developer\nLevels", 37, 9, 12, 12, true, 18226543);
    auto genaUser = CreditNode::create("GenaMorphosis", "Textures\nLevels", 467, 6, 3, 1, true, 10026833);
    auto toastUser = CreditNode::create("RealToastGD", "Levels", 275, 6, 3, 0, true, 26666582);

    //auto robtopUser = CreditNode::create("RobTop", "Levels", 4, 11, 3, 3, true, 71);
    auto andrexelUser = CreditNode::create("Andrexel", "Levels", 114, 8, 11, 70, true, 8327873);
    auto fatzUser = CreditNode::create("FatzFries", "\"Space Battle\" Boss Design\nIcons (Cube 5 - 12)", 235, 18, 12, 12, true, 14007342);
    auto cyanUser = CreditNode::create("cyanflower", "Vault Hints\nIcons", 2, 12, 3, 3, true, 21113321);

    CCArray* row1CreditArray = CCArray::create();
    CCArray* row2CreditArray = CCArray::create();

    row1CreditArray->addObject(capeUser);
    row1CreditArray->addObject(genaUser);
    row1CreditArray->addObject(toastUser);

    //row2CreditArray->addObject(robtopUser);
    row2CreditArray->addObject(andrexelUser);
    row2CreditArray->addObject(fatzUser);
    row2CreditArray->addObject(cyanUser);

    m_creditsLayer->addChild(capeUser);
    m_creditsLayer->addChild(genaUser);
    m_creditsLayer->addChild(toastUser);

    //m_creditsLayer->addChild(robtopUser);
    m_creditsLayer->addChild(andrexelUser);
    m_creditsLayer->addChild(fatzUser);
    m_creditsLayer->addChild(cyanUser);

    m_creditsLayer->addChild(creditsLabel);

    GameToolbox::alignItemsHorisontally(row1CreditArray, 115.f, ccp(winSize.width / 2, m_bgSprite->getContentHeight() - 70), false);
    GameToolbox::alignItemsHorisontally(row2CreditArray, 115.f, ccp(winSize.width / 2, m_bgSprite->getContentHeight() - 170), false);
}

void CreditsLayer::setupLevelsTab() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto levelsLabel = CCLabelBMFont::create("Levels", "bigFont.fnt");
    levelsLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight()));

    auto activeLevel = LevelNode::create(40, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Bugfixes)", 5, IconType::Cube);
    auto thunderZoneLevel = LevelNode::create(41, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 6, IconType::Cube);
    auto earthSplitterLevel = LevelNode::create(42, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 7, IconType::Cube);
    auto spaceBattleLevel = LevelNode::create(43, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>FatzFries</c>: (Boss Design)", 8, IconType::Cube);
    auto powerGloveLevel = LevelNode::create(44, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 13, IconType::Cube);

    auto paybackLevel = LevelNode::create(45, "<cg>GenaMorphosis</c>: (Layout, Deco)", 14, IconType::Cube);
    auto hyperchargedLevel = LevelNode::create(46, "<cg>GenaMorphosis</c>: (Deco)\n<cl>Capeling</c>: (Layout, Minor Details)", 15, IconType::Cube);
    auto reverieLevel = LevelNode::create(47, "<cg>Andrexel</c>: (Deco)\n<cl>GenaMorphosis</c>: (Layout)\n<cy>Capeling</c>: (Bugfixes & Minor Details)", 16, IconType::Cube);
    auto groundZeroLevel = LevelNode::create(48, "<cg>RealToastGD</c>: (Deco)\n<cl>Capeling</c>: (Layout)", 17, IconType::Cube);
    auto ultrasonicLevel = LevelNode::create(49, "<cg>GenaMorphosis</c>: (Layout, Deco)", 2, IconType::Swing);

    CCArray* row1LevelArray = CCArray::create();
    CCArray* row2LevelArray = CCArray::create();

    row1LevelArray->insertObject(activeLevel, 0);
    row1LevelArray->insertObject(thunderZoneLevel, 0);
    row1LevelArray->insertObject(earthSplitterLevel, 0);
    row1LevelArray->insertObject(spaceBattleLevel, 0);
    row1LevelArray->insertObject(powerGloveLevel, 0);

    row2LevelArray->insertObject(paybackLevel, 0);
    row2LevelArray->insertObject(hyperchargedLevel, 0);
    row2LevelArray->insertObject(reverieLevel, 0);
    row2LevelArray->insertObject(groundZeroLevel, 0);
    row2LevelArray->insertObject(ultrasonicLevel, 0);

    GameToolbox::alignItemsVertically(row1LevelArray, 40.f, ccp((winSize.width / 2) - 200, winSize.height / 2));
    GameToolbox::alignItemsVertically(row2LevelArray, 40.f, ccp((winSize.width / 2) + 13, winSize.height / 2));

    auto levelsMenu = CCMenu::create();
    levelsMenu->setPosition(18.f, -12.f);

    levelsMenu->addChild(activeLevel);
    levelsMenu->addChild(thunderZoneLevel);
    levelsMenu->addChild(powerGloveLevel);
    levelsMenu->addChild(earthSplitterLevel);
    levelsMenu->addChild(spaceBattleLevel);

    levelsMenu->addChild(paybackLevel);
    levelsMenu->addChild(hyperchargedLevel);
    levelsMenu->addChild(reverieLevel);
    levelsMenu->addChild(groundZeroLevel);
    levelsMenu->addChild(ultrasonicLevel);

    m_levelsLayer->addChild(levelsLabel);
    m_levelsLayer->addChild(levelsMenu);
}

void CreditsLayer::setupDebugTab() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto debugLabel = CCLabelBMFont::create("Debug", "bigFont.fnt");
    debugLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight()));

    auto resetSave = CCMenuItemSpriteExtra::create(ButtonSprite::create("Reset Save Popup", 80, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 0.4f), this, menu_selector(CreditsLayer::onResetGameVar));
    auto resetOneTimeNotEnough = CCMenuItemSpriteExtra::create(ButtonSprite::create("Reset Not Enough Dialogue", 80, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 0.4f), this, menu_selector(CreditsLayer::onResetGameVar));
    auto resetEnoughCoins = CCMenuItemSpriteExtra::create(ButtonSprite::create("Reset Enough Coins Dialogue", 80, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 0.4f), this, menu_selector(CreditsLayer::onResetGameVar));

    resetSave->setTag(50);
    resetOneTimeNotEnough->setTag(51);
    resetEnoughCoins->setTag(52);

    auto debugMenu = CCMenu::create();
    debugMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(20.f));

    debugMenu->addChild(resetSave);
    debugMenu->addChild(resetOneTimeNotEnough);
    debugMenu->addChild(resetEnoughCoins);
    
    debugMenu->updateLayout();

    m_debugLayer->addChild(debugMenu);
    m_debugLayer->addChild(debugLabel);
}

void CreditsLayer::onChangeTab(CCObject* sender) {
    m_tab += sender->getTag();
    changeTab();
}

void CreditsLayer::onResetGameVar(CCObject* sender) {
    GameManager::get()->setUGV(fmt::format("{}", sender->getTag()).c_str(), false);
}

void CreditsLayer::changeTab() {

    if(m_tab == 0) {
        m_levelsLayer->setVisible(false);
        m_creditsLayer->setVisible(true);
        m_debugLayer->setVisible(false);
        m_backTabMenu->setVisible(false);
        m_forwardTabMenu->setVisible(true);
    }

    if(m_tab == 1) {
        m_levelsLayer->setVisible(true);
        m_creditsLayer->setVisible(false);
        m_debugLayer->setVisible(false);
        m_forwardTabMenu->setVisible(true);
        m_backTabMenu->setVisible(true);
        //m_forwardTabMenu->setVisible(false);
    }

    if(m_tab == 2) {
        m_levelsLayer->setVisible(false);
        m_creditsLayer->setVisible(false);
        m_debugLayer->setVisible(true);
        m_forwardTabMenu->setVisible(false);
        m_backTabMenu->setVisible(true);
    }
}

CreditsLayer* CreditsLayer::create(std::string const& title) {
    auto ret = new CreditsLayer();
    if(ret && ret->init(430.f, 270.f, title, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}