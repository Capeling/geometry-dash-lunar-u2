#pragma once
#include "../../defs/all.h"

class CreditNode : public CCNode {
protected:
    int m_accountID = 0;
    SimplePlayer* m_userIcon = nullptr;
    CCLabelBMFont* m_userName = nullptr;
    CCLabelBMFont* m_userReason = nullptr;
    CCMenuItemSpriteExtra* m_userButton = nullptr;
    $override
    bool init(const char* name, const char* reason, int iconID, int color1, int color2, int color3, bool glow, int accountID);
public:
    static CreditNode* create(const char* name, const char* reason, int iconID, int color1, int color2, int color3, bool glow, int accountID);
    void onUser(CCObject* sender);
};