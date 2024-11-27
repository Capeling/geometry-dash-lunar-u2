#include <nodes/LevelNode.h>

using namespace geode::prelude;

LevelNode* LevelNode::create(int audioID, std::string infoDesc, int iconID, IconType iconType, int levelID) {
    auto ret = new LevelNode();
    if(ret && ret->init(audioID, infoDesc, iconID, iconType, levelID)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LevelNode::init(int audioID, std::string infoDesc, int iconID, IconType iconType, int levelID) {
    if(!CCNode::init())
        return false;

    auto GM = GameManager::sharedState();

    m_levelIcon = SimplePlayer::create(1);
    m_levelIcon->updatePlayerFrame(iconID, iconType);
    m_levelIcon->setColor(GM->colorForIdx(17));
    m_levelIcon->setSecondColor(GM->colorForIdx(12));
    m_levelIcon->setGlowOutline(GM->colorForIdx(12));
    m_levelIcon->setScale(0.8f);
    addChild(m_levelIcon);

    m_levelLabel = CCLabelBMFont::create(LevelTools::getAudioTitle(audioID).c_str(), "goldFont.fnt");
    m_levelLabel->setPosition({20.f, 0.f});
    m_levelLabel->setAnchorPoint({0.0f, 0.5f});
    m_levelLabel->setScale(0.8f);
    m_levelLabel->limitLabelWidth(125.f, 0.8f, 0.f);
    addChild(m_levelLabel);

    auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    infoSpr->setScale(0.5f);

    m_infoBtn = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(LevelNode::onInfo));
    
    auto buttonMenu = CCMenu::create();
    buttonMenu->setPosition(m_levelLabel->getPositionX() + m_levelLabel->getScaledContentSize().width + 8, -2.5);
    buttonMenu->addChild(m_infoBtn);
    addChild(buttonMenu);

    m_audioID = audioID;
    m_levelID = levelID;
    m_infoDesc = infoDesc;

    setID("audio-"_spr + std::to_string(audioID) + "-level-node");

    return true;
}

void LevelNode::onInfo(CCObject* sender) {

    auto string = fmt::format("<cy>Online Level ID</c>: {}\n\n{}\n\n<cj>Song</c>: {} by <cp>{}</c>", m_levelID, m_infoDesc, LevelTools::getAudioTitle(m_audioID), LevelTools::nameForArtist(LevelTools::artistForAudio(m_audioID)));

    FLAlertLayer::create(LevelTools::getAudioTitle(m_audioID).c_str(), string.c_str(), "OK")->show();
}