#pragma once
#include "../../defs/all.h"
#include <Geode/ui/TextInput.hpp>

class VaultLayer : public CCLayer {
protected:
    TextInput* m_textInput = nullptr;
    CCLabelBMFont* m_title = nullptr;
    CCSprite* m_lunarMasterSpr = nullptr;
    CCMenuItemSpriteExtra* m_lunarMasterBtn = nullptr;
    CCSprite* m_bg = nullptr;
    CCLabelBMFont* m_response = nullptr;
    CCSprite* m_throneSpr = nullptr;
    CCParticleSystemQuad* m_throneParticles = nullptr;
    CCLabelBMFont* m_throneLabel = nullptr;
    CCMenuItemSpriteExtra* m_throneBtn = nullptr;
    CCMenu* m_throneMenu = nullptr;
    int m_messageID;
    int m_messageIndex;

public:
    bool init();
    static VaultLayer* create();
    static CCScene* scene();

    void onClose(CCObject*);
    void onSubmit(CCObject*);
    
    void keyBackClicked();
    void updateMessageLabel(std::string string, bool isSpecial);

    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int index, int messageID);
};