#include "../headers/LevelNode.h"

LevelNode* LevelNode::create(std::string levelName, std::string infoDesc, bool flipped, int audioID) {
    auto ret = new LevelNode();
    if(ret && ret->init(levelName, infoDesc, flipped, audioID)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LevelNode::init(std::string levelName, std::string infoDesc, bool flipped, int audioID) {
    if(!CCNode::init())
        return false;

    m_levelLabel = CCLabelBMFont::create(levelName.c_str(), "goldFont.fnt");
    m_levelLabel->setAnchorPoint({0.0f, 0.5f});
    m_levelLabel->setScale(0.8f);
    if(flipped) m_levelLabel->setPositionX(8);
    addChild(m_levelLabel);

    std::string lower;

    for(auto elem : std::string(levelName))
       lower += std::tolower(elem);

    auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    infoSpr->setScale(0.5f);

    m_infoBtn = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(LevelNode::onInfo));
    
    auto buttonMenu = CCMenu::create();
    if(flipped) {
        buttonMenu->setPosition(0, -3);
    } else {
        buttonMenu->setPosition(m_levelLabel->getPositionX() + m_levelLabel->getScaledContentSize().width + 8, -2.5);
    }
    buttonMenu->addChild(m_infoBtn);
    addChild(buttonMenu);

    m_levelName = levelName;
    m_infoDesc = infoDesc;
    m_audioID = audioID;

    setID(""_spr + lower + "-level-node");

    return true;
}

void LevelNode::onInfo(CCObject* sender) {

    auto string = fmt::format("{}\n\n<cj>Song</c>: {} by <cp>{}</c>", m_infoDesc, LevelTools::getAudioTitle(m_audioID), LevelTools::nameForArtist(LevelTools::artistForAudio(m_audioID)));

    FLAlertLayer::create(m_levelName.c_str(), string.c_str(), "OK")->show();
}