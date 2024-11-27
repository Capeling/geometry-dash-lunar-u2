#pragma once
#include <Geode/Geode.hpp>

class CreditsLayer : public geode::Popup<> {
protected:
    bool setup() override;
    void setupCreditsTab();
    void setupLevelsTab();
    void setupDebugTab();
    void changeTab();
    void onResetGameVar(cocos2d::CCObject* sender);
    void onNext(cocos2d::CCObject*);
    void onPrev(cocos2d::CCObject*);

    virtual void keyDown(cocos2d::enumKeyCodes key);

    CCMenuItemSpriteExtra* m_forwardTabBtn = nullptr;
    CCMenuItemSpriteExtra* m_backTabBtn = nullptr;

    cocos2d::CCMenu* m_forwardTabMenu = nullptr;
    cocos2d::CCMenu* m_backTabMenu = nullptr;

    cocos2d::CCLayer* m_creditsLayer = nullptr;
    cocos2d::CCLayer* m_levelsLayer = nullptr;
    cocos2d::CCLayer* m_debugLayer = nullptr;
    
    int m_tab = 0;

    int m_lastTab = 
    #ifdef DEBUG_ENABLED 
    2 
    #else 
    1 
    #endif
    ;
public:
    static CreditsLayer* create();
};