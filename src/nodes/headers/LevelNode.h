#pragma once
#include "../../defs/all.h"

class LevelNode : public CCNode {
protected:
    std::string m_levelName = "";
    std::string m_infoDesc = "";
    int m_audioID = 0;
    
    CCMenuItemSpriteExtra* m_infoBtn = nullptr;
    CCLabelBMFont* m_levelLabel = nullptr;
    $override
    bool init(std::string levelName, std::string infoDesc, bool flipped, int audioID);
public:
    static LevelNode* create(std::string levelName, std::string infoDesc, bool flipped, int audioID);
    void onInfo(CCObject* sender);
};