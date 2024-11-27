#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>

class $modify(HookedMusicDownloadManager, MusicDownloadManager) {
    $override
    gd::string pathForSFXFolder(int sfxID);

    $override
    gd::string pathForSongFolder(int songID);
};