#include "../headers/HookedItemInfoPopup.h"

bool HookedItemInfoPopup::init(int itemID, UnlockType unlockType) {
    if(!ItemInfoPopup::init(itemID, unlockType))
        return false;
    auto buttonMenu = getChildOfType<CCMenu>(m_mainLayer, 0);
    auto okButton = getChildOfType<CCMenuItemSpriteExtra>(buttonMenu, 0);

    okButton->removeFromParentAndCleanup(false);
    buttonMenu->removeAllChildren();

    buttonMenu->addChild(okButton);
    return true;
}