#include "../../defs/all.h"
#include <Geode/modify/LoadingLayer.hpp>

class $modify(HookedLoadingLayer, LoadingLayer) {
    $override
    bool init(bool fromReload);

    $override
    void loadingFinished();
};