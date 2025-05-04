#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

class $modify(HookedGManager, GManager) {
public:
    $override
    void setup();
};