#include "../headers/HookedLocalLevelManager.h"

gd::string HookedLocalLevelManager::getMainLevelString(int id) {

    auto file = CCString::createWithFormat("level-%i.txt"_spr, id);
    if(file == nullptr) return "";
    auto content = CCString::createWithContentsOfFile(file->getCString());
    if(content == nullptr) return "";
    //clipboard::write(ZipUtils::compressString(content->getCString(), false, 11)); 

    return gd::string(content->getCString());
    return LocalLevelManager::getMainLevelString(id);
    //if(id > 1000) return LocalLevelManager::getMainLevelString(id);
}