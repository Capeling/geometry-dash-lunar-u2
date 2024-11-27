#pragma once
#include <Geode/Geode.hpp>

//now if you are an experienced geode dev you may know about geode::popup
//and if i know about it, the question is, why didnt i use it?
//the answer is really easy, i just felt like doing it this way lol

class SavePopup : public FLAlertLayer {
protected:
    $override
    virtual bool init();

    $override
    virtual void keyBackClicked();

    cocos2d::extension::CCScale9Sprite* m_background = nullptr;
    cocos2d::extension::CCScale9Sprite* m_darkenedArea = nullptr;
    cocos2d::CCLabelBMFont* m_title = nullptr;
    TextArea* m_textArea = nullptr;
    CCMenuItemSpriteExtra* m_okBtn = nullptr;

public:
    static SavePopup* create();
    
    void onClose(CCObject*);
};