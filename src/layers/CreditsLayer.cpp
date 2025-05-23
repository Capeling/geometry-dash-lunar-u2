#include <layers/CreditsLayer.h>
#include <nodes/CreditNode.h>
#include <nodes/LevelNode.h>

using namespace geode::prelude;

bool CreditsLayer::setup() {
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
    m_creditsLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

    m_mainLayer->addChild(m_levelsLayer, 1);
    m_levelsLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

    m_mainLayer->addChild(m_debugLayer, 1);
    m_debugLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

    auto forwardTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    forwardTabSpr->setFlipX(true);
    m_forwardTabBtn = CCMenuItemSpriteExtra::create(forwardTabSpr, this, menu_selector(CreditsLayer::onNext));

    m_forwardTabMenu = CCMenu::create();
    m_forwardTabMenu->setPosition(director->getScreenRight() - 25, winSize.height / 2);
    m_forwardTabMenu->addChild(m_forwardTabBtn);

    auto backTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    m_backTabBtn = CCMenuItemSpriteExtra::create(backTabSpr, this, menu_selector(CreditsLayer::onPrev));

    m_backTabMenu = CCMenu::create();
    m_backTabMenu->setPosition(director->getScreenLeft() + 25, winSize.height / 2);
    m_backTabMenu->addChild(m_backTabBtn);

    m_mainLayer->addChildAtPosition(m_forwardTabMenu, Anchor::Right, ccp(25, 0));
    m_mainLayer->addChildAtPosition(m_backTabMenu, Anchor::Left, ccp(-25, 0));

    changeTab();

    return true;
}

void CreditsLayer::setupCreditsTab() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto creditsLabel = CCLabelBMFont::create("Credits", "bigFont.fnt");
    creditsLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight()));

    auto capeUser = CreditNode::create("Capeling", "Mod Developer\nLevels", 70, 41, 12, 12, true, 18226543);
    auto genaUser = CreditNode::create("GenaMorphosis", "Textures\nLevels", 467, 6, 83, 72, true, 10026833);
    auto toastUser = CreditNode::create("RealToastGD", "Levels\nHypercharged Remix", 339, 12, 75, 3, true, 26666582);

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

    //268402
    auto listLabel = CCLabelBMFont::create("Online list ID: 268402", "chatFont.fnt");
    listLabel->setPosition({winSize.width / 2, (winSize.height / 2) - 123});
    listLabel->setScale(0.5f);
    listLabel->setOpacity(255 / 2);
    m_levelsLayer->addChild(listLabel);

    auto activeLevel = LevelNode::create(40, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Bugfixes)", 5, IconType::Cube, 102794116);
    auto thunderZoneLevel = LevelNode::create(41, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 6, IconType::Cube, 102793978);
    auto earthSplitterLevel = LevelNode::create(42, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 7, IconType::Cube, 102793986);
    auto spaceBattleLevel = LevelNode::create(43, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>FatzFries</c>: (Boss Design)", 8, IconType::Cube, 102794046);
    auto powerGloveLevel = LevelNode::create(44, "<cg>GenaMorphosis</c>: (Layout, Deco)\n<cl>Capeling</c>: (Camera Improvements)", 13, IconType::Cube, 105680408);

    auto paybackLevel = LevelNode::create(45, "<cg>GenaMorphosis</c>: (Layout, Deco)", 14, IconType::Cube, 105680505);
    auto hyperchargedLevel = LevelNode::create(46, "<cg>GenaMorphosis</c>: (Deco)\n<cl>Capeling</c>: (Layout, Minor Details)", 15, IconType::Cube, 105680423);
    auto reverieLevel = LevelNode::create(47, "<cg>Andrexel</c>: (Deco)\n<cl>GenaMorphosis</c>: (Layout)\n<cy>Capeling</c>: (Bugfixes & Minor Details)", 16, IconType::Cube, 105680313);
    auto groundZeroLevel = LevelNode::create(48, "<cg>RealToastGD</c>: (Deco)\n<cl>Capeling</c>: (Layout)", 17, IconType::Cube, 105685405);
    auto ultrasonicLevel = LevelNode::create(49, "<cg>GenaMorphosis</c>: (Layout, Deco)", 2, IconType::Swing, 105680463);

    CCMenu* row1LevelMenu = CCMenu::create();
    CCMenu* row2LevelMenu = CCMenu::create();

    row1LevelMenu->addChild(activeLevel, 0);
    row1LevelMenu->addChild(thunderZoneLevel, 0);
    row1LevelMenu->addChild(earthSplitterLevel, 0);
    row1LevelMenu->addChild(spaceBattleLevel, 0);
    row1LevelMenu->addChild(powerGloveLevel, 0);

    row2LevelMenu->addChild(paybackLevel, 0);
    row2LevelMenu->addChild(hyperchargedLevel, 0);
    row2LevelMenu->addChild(reverieLevel, 0);
    row2LevelMenu->addChild(groundZeroLevel, 0);
    row2LevelMenu->addChild(ultrasonicLevel, 0);

    row1LevelMenu->setPosition(ccp((winSize.width / 2) - 200, winSize.height / 2));
    row2LevelMenu->setPosition(ccp((winSize.width / 2) + 13, winSize.height / 2));

    row1LevelMenu->setLayout(ColumnLayout::create()->setGap(40.f));
    row2LevelMenu->setLayout(ColumnLayout::create()->setGap(40.f));

    // GameToolbox::alignItemsVertically(row1LevelArray, 40.f, ccp((winSize.width / 2) - 200, winSize.height / 2));
    // GameToolbox::alignItemsVertically(row2LevelArray, 40.f, ccp((winSize.width / 2) + 13, winSize.height / 2));

    auto levelsMenu = CCMenu::create();
    levelsMenu->setPosition(18.f, -12.f);

    levelsMenu->addChild(row1LevelMenu);
    levelsMenu->addChild(row2LevelMenu);

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
    auto resetTimeReborn = CCMenuItemSpriteExtra::create(ButtonSprite::create("Reset Time Reborn Popup", 80, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 0.4f), this, menu_selector(CreditsLayer::onResetGameVar));

    resetSave->setTag(50);
    resetOneTimeNotEnough->setTag(51);
    resetEnoughCoins->setTag(52);
    resetTimeReborn->setTag(53);

    auto debugMenu = CCMenu::create();
    debugMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(20.f));

    debugMenu->addChild(resetSave);
    debugMenu->addChild(resetOneTimeNotEnough);
    debugMenu->addChild(resetEnoughCoins);
    debugMenu->addChild(resetTimeReborn);
    
    debugMenu->updateLayout();

    m_debugLayer->addChild(debugMenu);
    m_debugLayer->addChild(debugLabel);
}

void CreditsLayer::onNext(CCObject*) {
    m_tab++;
    changeTab();
}

void CreditsLayer::onPrev(CCObject*) {
    m_tab--;
    changeTab();
}

void CreditsLayer::onResetGameVar(CCObject* sender) {
    GameManager::get()->setUGV(fmt::format("{}", sender->getTag()).c_str(), false);
}

void CreditsLayer::changeTab() {

    m_creditsLayer->setVisible(false);
    m_levelsLayer->setVisible(false);
    m_debugLayer->setVisible(false);

    if(m_tab > m_lastTab)
        m_tab = m_lastTab;

    if(m_tab < 0)
        m_tab = 0;

    if(m_tab == 0) {
        m_creditsLayer->setVisible(true);
    }

    if(m_tab == 1) {
        m_levelsLayer->setVisible(true);
    }

    if(m_tab == 2) {
        m_debugLayer->setVisible(true);
    }

    if(m_tab <= 0) {
        m_backTabMenu->setVisible(false);
    } else {
        m_backTabMenu->setVisible(true);
    }

    if(m_tab >= m_lastTab) {
        m_forwardTabMenu->setVisible(false);
    } else {
        m_forwardTabMenu->setVisible(true);
    }
}

CreditsLayer* CreditsLayer::create() {
    auto ret = new CreditsLayer();
    if(ret && ret->initAnchored(430.f, 270.f, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void CreditsLayer::keyDown(cocos2d::enumKeyCodes key) {
    
    if(key == enumKeyCodes::KEY_Right) 
        onNext(nullptr);
    if(key == enumKeyCodes::KEY_Left)
        onPrev(nullptr);
    
    Popup::keyDown(key);
}