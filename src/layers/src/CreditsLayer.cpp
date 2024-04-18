#include "../headers/CreditsLayer.h"
#include "../../nodes/headers/CreditNode.h"

bool CreditsLayer::setup(std::string const& title) {
    setID("credits-layer"_spr);
    setTitle(title, "bigFont.fnt", 0.8f);

    auto capeUser = CreditNode::create("Capeling", "Mod Developer\nLevel 9 Layout", 475, 41, 52, 52, true, 18226543);
    auto genaUser = CreditNode::create("GenaMorphosis", "Levels (1-10)", 467, 6, 3, 1, true, 10026833);
    auto fatzUser = CreditNode::create("FatzFries", "Icons (Cube 5-12)", 235, 18, 12, 12, true, 14007342);
    auto cyanUser = CreditNode::create("CyanFlower", "Icons", 2, 12, 3, 3, true, 21113321);

    CCMenu* creditMenu = CCMenu::create();
    creditMenu->addChild(capeUser);
    creditMenu->addChild(genaUser);
    creditMenu->addChild(fatzUser);
    creditMenu->addChild(cyanUser);

    creditMenu->setLayout(AxisLayout::create(Axis::Row)->setAxisAlignment(AxisAlignment::Even)->setCrossAxisOverflow(true));
    creditMenu->setContentWidth(m_mainLayer->getContentWidth() - 10);
    creditMenu->updateLayout();

    m_mainLayer->addChildAtPosition(creditMenu, Anchor::Center, ccp(0, -10));

    return true;
}

CreditsLayer* CreditsLayer::create(std::string const& title) {
    auto ret = new CreditsLayer();
    if(ret && ret->initAnchored(450.f, 170.f, title, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}