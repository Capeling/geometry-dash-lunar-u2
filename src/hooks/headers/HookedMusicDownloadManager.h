#pragma once
#include "../../defs/all.h"
#include <Geode/modify/MusicDownloadManager.hpp>

class $modify(HookedMusicDownloadManager, MusicDownloadManager) {
    $override
    gd::string pathForSFXFolder(int sfxID);

    $override
    gd::string pathForSongFolder(int songID);
};