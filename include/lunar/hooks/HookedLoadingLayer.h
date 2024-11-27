#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

class $modify(HookedLoadingLayer, LoadingLayer) {
    $override
    bool init(bool fromReload);

    $override
    void loadAssets();
};