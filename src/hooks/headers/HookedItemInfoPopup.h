#pragma once
#include "../../defs/all.h"
#include <Geode/modify/ItemInfoPopup.hpp>

class $modify(HookedItemInfoPopup, ItemInfoPopup) {
    $override
    bool init(int itemID, UnlockType unlockType);
};