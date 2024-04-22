#pragma once
#include "../../defs/all.h"

class LevelNode : public CCNode {
protected:
    std::string m_infoDesc = "";
    int m_audioID = 0;
    
    SimplePlayer* m_levelIcon = nullptr;
    CCMenuItemSpriteExtra* m_infoBtn = nullptr;
    CCLabelBMFont* m_levelLabel = nullptr;
    $override
    bool init(int audioID, std::string infoDesc, int iconID, IconType iconType);
public:
    static LevelNode* create(int audioID, std::string infoDesc, int iconID, IconType iconType);
    void onInfo(CCObject* sender);
};