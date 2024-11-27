#pragma once
#include <Geode/Geode.hpp>

class LevelNode : public cocos2d::CCNode {
protected:
    std::string m_infoDesc = "";
    int m_audioID = 0;
    int m_levelID = 0;
    
    SimplePlayer* m_levelIcon = nullptr;
    CCMenuItemSpriteExtra* m_infoBtn = nullptr;
    cocos2d::CCLabelBMFont* m_levelLabel = nullptr;
    $override
    bool init(int audioID, std::string infoDesc, int iconID, IconType iconType, int levelID);
public:
    static LevelNode* create(int audioID, std::string infoDesc, int iconID, IconType iconType, int levelID);
    void onInfo(CCObject* sender);
};