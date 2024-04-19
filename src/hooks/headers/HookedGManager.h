#pragma once
#include "../../defs/all.h"
#include <Geode/modify/GManager.hpp>

class $modify(HookedGManager, GManager) {
public:
    $override
    void setup();
};