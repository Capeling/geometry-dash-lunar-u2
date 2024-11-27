#include <hooks/HookedGManager.h>

using namespace geode::prelude;

void HookedGManager::setup() {

    auto compare = std::string(m_fileName);

    compare.insert(std::string_view(compare).find(".dat"), "Lunar");

    m_fileName = compare;
    GManager::setup();
}