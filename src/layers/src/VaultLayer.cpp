#include "../headers/VaultLayer.h"
#include <algorithm>
#include <cctype>
#include <string>

bool VaultLayer::init() {
    if(!CCLayer::init())
        return false;

    auto director = CCDirector::get();
    auto winSize = director->getWinSize();

    m_bg = CCSprite::create("GJL_lunarBG_001.png"_spr);
    m_bg->setAnchorPoint({0.f, 0.f});
    addChild(m_bg, -2);

    m_bg->setScaleX((winSize.width + 10.f) / m_bg->getTextureRect().size.width);
    m_bg->setScaleY((winSize.height + 10.f) / m_bg->getTextureRect().size.height);
    m_bg->setPosition(ccp(-5, -5));

    m_title = CCLabelBMFont::create("Lunar Hideout", "goldFont.fnt");
    addChildAtPosition(m_title, Anchor::Top, ccp(0, -22), false);

    m_textInput = TextInput::create(180, "...");
    m_textInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    m_textInput->setMaxCharCount(20);

    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 65), false);

    m_response = CCLabelBMFont::create("", "bigFont.fnt");
    updateMessageLabel("It's you again...", false);

    addChildAtPosition(m_response, Anchor::Center, ccp(0, 105), false);

    m_lunarMasterSpr = CCSprite::createWithSpriteFrameName("GJL_lunarMaster_001.png"_spr);
    m_lunarMasterSpr->setScale(1.15);

    m_lunarMasterBtn = CCMenuItemSpriteExtra::create(m_lunarMasterSpr, this, menu_selector(VaultLayer::onSubmit));

    auto lunarMasterMenu = CCMenu::create();
    lunarMasterMenu->addChild(m_lunarMasterBtn);

    addChildAtPosition(lunarMasterMenu, Anchor::Center, ccp(0, -35), false);

    auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    auto backBtn = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(VaultLayer::onClose));

    bool hasSeenAnim = Mod::get()->getSavedValue<bool>("has-seen-anim");
    m_playSpr = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    m_playSpr->setScale(0.5f);

    m_playBtn = CCMenuItemSpriteExtra::create(m_playSpr, this, nullptr);

    m_playMenu = CCMenu::create();
    m_playMenu->addChild(m_playBtn);

    if(!hasSeenAnim) {
        m_playSpr->setScale(1.f);
        auto scaleTo = CCScaleTo::create(0.5f, 0.5f);
        auto easeInOut = CCEaseInOut::create(scaleTo, 2.0f);
        m_playSpr->runAction(easeInOut);
    }

    auto backMenu = CCMenu::create();
    backMenu->addChild(backBtn);
    
    addChildAtPosition(backMenu, Anchor::TopLeft, ccp(25, -22), false);
    addChildAtPosition(m_playMenu, Anchor::BottomRight, ccp(-50, 50), false);

    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    GameManager::sharedState()->fadeInMusic("secretLoop.mp3"_spr);
    return true;
}

void VaultLayer::updateMessageLabel(std::string message, bool isSpecial) {
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.f);
    if(isSpecial) {
        m_response->setColor({ 63, 217, 255 });
    } else {
        m_response->setColor({255, 255, 255});
    }
}

void VaultLayer::onSubmit(CCObject*) {
    std::string response = getMessage();
    std::string lower;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    for(auto elem : m_textInput->getString())
       lower += std::tolower(elem);

    m_textInput->setString("");

    if(std::string_view(lower) == "throne room") {

    }

    if(std::string_view(lower) == std::string_view("attention") && !AM->isAchievementEarned("geometry.ach.lunar.vault01")) {
        response = "Attention, to what is happening...";
        GM->reportAchievementWithID("geometry.ach.lunar.vault01", 100, false);
        return updateMessageLabel(response, false);
    }

    if(std::string_view(lower) == std::string_view("lucky") && !AM->isAchievementEarned("geometry.ach.lunar.vault02")) {
        response = "It's your lucky day!";
        GM->reportAchievementWithID("geometry.ach.lunar.vault02", 100, false);
        return updateMessageLabel(response, false);
    }

    if(std::string_view(lower) == std::string_view("stellar") && !AM->isAchievementEarned("geometry.ach.lunar.vault03")) {
        response = "SPAAAAACE!";
        GM->reportAchievementWithID("geometry.ach.lunar.vault03", 100, false);
        return updateMessageLabel(response, false);
    }

    if(std::string_view(lower) == std::string_view("monochromatic") && !AM->isAchievementEarned("geometry.ach.lunar.vault04")) {
        response = "Ah, right! Her name is Mono.";
        GM->reportAchievementWithID("geometry.ach.lunar.vault04", 100, false);
        return updateMessageLabel(response, false);
    }

    if(m_messageID == 3 || m_messageID == 4 || m_messageID == 5 || m_messageID == 6) {
        return updateMessageLabel(response, true);
    }

    updateMessageLabel(response, false);
}

std::string VaultLayer::getMessage() {
    int rand = std::rand() % 39 + 1;
    if(m_messageID == 0) {
        m_messageID = rand;
        m_messageIndex = 0;
        std::string message = getThreadMessage(m_messageIndex, m_messageID);
        if(message == "") message = getBasicMessage();
        m_messageIndex++;
        return message;
    } else {
        auto ret = getThreadMessage(m_messageIndex++, m_messageID);
        if(ret == "") ret = getBasicMessage();
        return ret;
    }
}

std::string VaultLayer::getThreadMessage(int index, int messageID) {

    auto AM = AchievementManager::sharedState();

    if(messageID == 1) {
        switch(index) {
            case 0: return "Gah! You have too much free time";
            case 1: return "You have, like, so many levels available";
            case 2: return "Why won't you go play them?";
            case 3: return "So I can rest...";
            case 4: return "...";
            case 5: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
    if(messageID == 2) {
        switch(index) {
            case 0: return "I'm going to sleep";
            case 1: return "...";
            case 2: return ".....";
            case 3: return "......!";
            case 4: return "Gah! I had a nightmare!";
            case 5: return "It was about you, how ironic";
            case 6: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
        if(messageID == 3 && !AM->isAchievementEarned("geometry.ach.lunar.vault04")) {
        switch(index) {
            case 0: return "Legends tell of a girl...";
            case 1: return "Her hair flows like a waterfall...";
            case 2: return "Her skin is as pale as the light...";
            case 3: return "And her eyes reflect her emptiness";
            case 4: return "...not enough?";
            case 5: return "Well, they say she looks grayscale";
            case 6: return "Colorless, even...";
            case 7: return "What was that word again?";
            case 8: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
        if(messageID == 4 && !AM->isAchievementEarned("geometry.ach.lunar.vault01")) {
        switch(index) {
            case 0: return "They say people aren't paying enough";
            case 1: return "Paying what?";
            case 2: return "I don't remember...";
            case 3: return "But it has something to do with awareness";
            case 4: return "Realization, of what's occurring around you";
            case 5: return "Observation, of what you are witnessing";
            case 6: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
        if(messageID == 5 && !AM->isAchievementEarned("geometry.ach.lunar.vault02")) {
        switch(index) {
            case 0: return "It hasn't been my day in years";
            case 1: return "People keep bothering me...";
            case 2: return "People like you";
            case 3: return "You're probably having a great day";
            case 4: return "A day better than mine...";
            case 5: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
        if(messageID == 6 && !AM->isAchievementEarned("geometry.ach.lunar.vault03")) {
        switch(index) {
            case 0: return "The night sky looks wonderful";
            case 1: return "Stars shining across it all...";
            case 2: return "If only I could leave this place and see those again";
            case 3: return "That would be lovely";
            case 4: return "Alas, I cannot";
            case 5: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
    if(messageID == 7) {
        switch(index) {
            case 0: return "The big one told me I was good at puns";
            case 1: return "He left me to rot after I told him one";
            case 2: return "Wanna hear it?";
            case 3: return "What takes years to develop and is on top?";
            case 4: return "A robot!";
            case 5: return "...it was funnier in my head, I swear";
            case 6: return "Ah, how much I miss the big one";
            case 7: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
    if(messageID == 8) {
        switch(index) {
            case 0: return "There once was a traveller";
            case 1: return "They say he was made of slime";
            case 2: return "Whatever that means...";
            case 3: return "He left the world to explore the universe";
            case 4: return "Barely anyone has seen him since";
            case 5: return "But those that have say he's...";
            case 6: return "Interesting";
            case 7: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
    if(messageID == 9) {
        switch(index) {
            case 0: return "I've been thinking";
            case 1: return "What if, by chance";
            case 2: return "You pressed that arrow button?";
            case 3: m_messageID = 0; m_messageIndex = 0; return "";
        }
    }
    m_messageID = 0;
    m_messageIndex = 0;
    return "";
}

std::string VaultLayer::getBasicMessage() {
    int rand = std::rand() % 14 + 1;
    switch(rand) {
        case 1: return "It's you again...";
        case 2: return "Have you ever heard of personal space?";
        case 3: return "...";
        case 4: return "Gah!";
        case 5: return "I'll stay here until the end of my life...";
        case 6: return "Go home";
        case 7: return "You test my patience...";
        case 8: return "Stop bothering me";
        case 9: return "Leave me alone!";
        case 10: return "What are you doing?!";
        case 11: return "Go bother someone else.";
        case 12: return "What's the point of this? What are you going to achieve?";
        case 13: return "Who even let you in?!";
        case 14: return "Can you even read?!";
        case 15: return "You have too much free time...";
        case 16: return "Spend your time somewhere else";
        case 17: return "Don't you have levels to beat?";
        case 18: return "The stars are bright and yet you waste your time here";
        case 19: return "Just leave this place already!";
        case 20: return "Aaaaarrrgh!!";
        case 21: return ".....";
        case 22: return ".......";
        case 23: return "And yet you remain here...";
        case 24: return "The shadow wizards locked me here...";
        case 25: return "I'm starving... get it?";
        case 26: return "Every time I blink, I still see you";
        case 27: return "I haven't had a rest in a while";
        default: return "...";
    }
    return "";
}

void VaultLayer::onClose(CCObject*) {
    CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, LevelSelectLayer::scene(10)));
    GameManager::sharedState()->fadeInMenuMusic();
}

void VaultLayer::keyBackClicked() {
    onClose(nullptr);
}

VaultLayer* VaultLayer::create() {
    auto ret = new VaultLayer();
    if(ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

CCScene* VaultLayer::scene() {
    auto ret = CCScene::create();
    ret->addChild(VaultLayer::create());
    return ret;
}
