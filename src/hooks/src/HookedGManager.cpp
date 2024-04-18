#include "../headers/HookedGManager.h"

void HookedGManager::setup() {

    auto compare = std::string(m_fileName);

    compare.insert(std::string_view(compare).find(".dat"), "Lunar");

    m_fileName = compare;
    GManager::setup();
    log::info("m_fileName: {}", m_fileName);
}

void HookedGManager::saveGMTo(gd::string file) {
    /*auto compare = std::string(file);
    if(!std::string_view(compare).starts_with("CCBetterInfo")) {
        compare.insert(compare.find(".dat"), "Lunar");
    }
    log::info("savegm: {}", compare);*/
    GManager::saveGMTo(file);
}

void HookedGManager::loadDataFromFile(gd::string const& file) {
    /*auto compare = std::string(file);
    if(!std::string_view(compare).starts_with("CCBetterInfo")) {
        compare.insert(compare.find(".dat"), "Lunar");
    }
    log::info("loaddata: {}", compare);*/
    GManager::loadDataFromFile(file);
}