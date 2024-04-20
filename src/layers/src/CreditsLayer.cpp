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

    setupCreditsTab();
    setupLevelsTab();

    m_mainLayer->addChild(m_creditsLayer, 1);
    m_mainLayer->addChild(m_levelsLayer, 1);

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

    auto capeUser = CreditNode::create("Capeling", "Mod Developer\nLevels", 141, 76, 40, 40, true, 18226543);
    auto genaUser = CreditNode::create("GenaMorphosis", "Levels", 467, 6, 3, 1, true, 10026833);

    //auto andrexelUser = CreditNode::create("?", "Levels", 114, 8, 11, 70, true, 8327873);
    auto andrexelUser = CreditNode::create("?", "Levels", 1, 1, 1, 1, true, 72);
    auto fatzUser = CreditNode::create("FatzFries", "\"Space Battle\" Boss Design\nIcons (Cube 5 - 12)", 235, 18, 12, 12, true, 14007342);
    auto cyanUser = CreditNode::create("CyanFlower", "Icons", 2, 12, 3, 3, true, 21113321);

    CCArray* row1CreditArray = CCArray::create();
    CCArray* row2CreditArray = CCArray::create();

    row1CreditArray->addObject(capeUser);
    row1CreditArray->addObject(genaUser);

    row2CreditArray->addObject(andrexelUser);
    row2CreditArray->addObject(fatzUser);
    row2CreditArray->addObject(cyanUser);

    m_creditsLayer->addChild(capeUser);
    m_creditsLayer->addChild(genaUser);

    m_creditsLayer->addChild(andrexelUser);
    m_creditsLayer->addChild(fatzUser);
    m_creditsLayer->addChild(cyanUser);

    m_creditsLayer->addChild(creditsLabel);

    GameToolbox::alignItemsHorisontally(row1CreditArray, 125.f, ccp(winSize.width / 2, m_bgSprite->getContentHeight() - 70), false);
    GameToolbox::alignItemsHorisontally(row2CreditArray, 115.f, ccp(winSize.width / 2, m_bgSprite->getContentHeight() - 170), false);
}

void CreditsLayer::setupLevelsTab() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto levelsLabel = CCLabelBMFont::create("Levels", "bigFont.fnt");
    levelsLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight()));

    auto activeLevel = LevelNode::create("Active", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Bugfixes)", false, 40);
    auto thunderZoneLevel = LevelNode::create("ThunderZone", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", false, 41);
    auto earthSplitterLevel = LevelNode::create("Earthsplitter", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", false, 42);
    auto spaceBattleLevel = LevelNode::create("Space Battle", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>FatzFries</c>: (Boss Design)", false, 43);
    auto powerGloveLevel = LevelNode::create("Power Glove", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", false, 44);

    auto paybackLevel = LevelNode::create("Payback", "<cg>GenaMorphosis</c>: (Layout, Deco)", false, 45);
    auto hyperchargedLevel = LevelNode::create("No...", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Layout)", false, 46);
    auto reverieLevel = LevelNode::create("No...", "<cg>Andrexel</c>: (Deco)\n<cl>GenaMorphosis</c>: (Layout)", false, 47);
    auto groundZeroLevel = LevelNode::create("No...", "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Layout)", false, 48);
    auto ultrasonicLevel = LevelNode::create("No...", "<cg>GenaMorphosis</c>: (Layout, Deco)", false, 49);

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

void CreditsLayer::onChangeTab(CCObject* sender) {
    m_tab += sender->getTag();
    changeTab();
}

void CreditsLayer::changeTab() {

    log::info("m_tab: {}", m_tab);

    if(m_tab == 0) {
        m_levelsLayer->setVisible(false);
        m_creditsLayer->setVisible(true);
        m_backTabMenu->setVisible(false);
        m_forwardTabMenu->setVisible(true);
    }

    if(m_tab == 1) {
        m_levelsLayer->setVisible(true);
        m_creditsLayer->setVisible(false);
        m_backTabMenu->setVisible(true);
        m_forwardTabMenu->setVisible(false);
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