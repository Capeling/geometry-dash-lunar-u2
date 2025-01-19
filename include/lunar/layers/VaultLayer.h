#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>

class VaultLayer : public cocos2d::CCLayer {
protected:
    geode::TextInput* m_textInput = nullptr;
    cocos2d::CCLabelBMFont* m_title = nullptr;
    cocos2d::CCSprite* m_lunarMasterSpr = nullptr;
    CCMenuItemSpriteExtra* m_lunarMasterBtn = nullptr;
    cocos2d::CCSprite* m_bg = nullptr;
    cocos2d::CCLabelBMFont* m_response = nullptr;
    cocos2d::CCSprite* m_throneSpr = nullptr;
    cocos2d::CCParticleSystemQuad* m_throneParticles = nullptr;
    cocos2d::CCLabelBMFont* m_throneLabel = nullptr;
    CCMenuItemSpriteExtra* m_throneBtn = nullptr;
    cocos2d::CCMenu* m_throneMenu = nullptr;

    cocos2d::CCSprite* m_ruinSpr = nullptr;
    cocos2d::CCLabelBMFont* m_ruinLabel = nullptr;
    CCMenuItemSpriteExtra* m_ruinBtn = nullptr;
    cocos2d::CCMenu* m_ruinMenu = nullptr;
    cocos2d::CCArray* m_coinArray = nullptr;
    int m_messageID;
    int m_messageIndex;

public:
    bool init();
    static VaultLayer* create();
    static cocos2d::CCScene* scene();

    void onClose(CCObject*);
    void onSubmit(CCObject*);
    void onRuin(CCObject*);
    
    void playStep1();

    void keyBackClicked();
    void updateMessageLabel(std::string string, bool isSpecial);

    void timeReborn();

    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int index, int messageID);
};