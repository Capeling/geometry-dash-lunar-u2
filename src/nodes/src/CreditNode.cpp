#include "../headers/CreditNode.h"

CreditNode* CreditNode::create(const char* name, const char* reason, int iconID, int color1, int color2, int color3, bool glow, int accountID) {
    auto ret = new CreditNode();
    if(ret && ret->init(name, reason, iconID, color1, color2, color3, glow, accountID)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CreditNode::init(const char* name, const char* reason, int iconID, int color1, int color2, int color3, bool glow, int accountID) {
    if(!CCNode::init())
        return false;

    auto GM = GameManager::get();

    m_userName = CCLabelBMFont::create(name, "goldFont.fnt");
    m_userName->setScale(0.6f);
    m_userName->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    m_userName->limitLabelWidth(180.f, 0.6f, 0.f);

    std::string lower;

    for(auto elem : std::string(name))
       lower += std::tolower(elem);

    m_userButton = CCMenuItemSpriteExtra::create(m_userName, this, menu_selector(CreditNode::onUser));

    m_userIcon = SimplePlayer::create(iconID);

    m_userIcon->setColor(GM->colorForIdx(color1));
    m_userIcon->setSecondColor(GM->colorForIdx(color2));
    if(glow) {
        m_userIcon->setGlowOutline(GM->colorForIdx(color3));
        m_userIcon->enableCustomGlowColor(GM->colorForIdx(color3));
    }

    m_userIcon->setPosition({0, 0});
    m_userIcon->setScale(1.2f);

    m_userReason = CCLabelBMFont::create(reason, "chatFont.fnt");
    m_userReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    m_userReason->setAnchorPoint({0.5f, 1.0f});
    m_userReason->setPosition({0, -22.f});
    m_userReason->setScale(0.7f);

    CCMenu* userMenu = CCMenu::create();
    userMenu->setPosition({0, 31});

    userMenu->addChild(m_userButton);
    addChild(userMenu);
    addChild(m_userIcon);
    addChild(m_userReason);

    m_accountID = accountID;
    setID(""_spr + lower + "-credit-node");

    return true;
}

void CreditNode::onUser(CCObject* sender) {
    ProfilePage::create(m_accountID, false)->show();
}