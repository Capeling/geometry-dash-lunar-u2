#include <hooks/HookedMusicDownloadManager.h>

using namespace geode::prelude;

gd::string HookedMusicDownloadManager::pathForSFXFolder(int sfxID) {
    return ""_spr;
    std::string original = MusicDownloadManager::pathForSFXFolder(sfxID);
    log::debug("sfx: {}", original);
    if(original == "sfx/") original = ""_spr;
    log::debug("sfx2: {}", original);

    return original;
}

gd::string HookedMusicDownloadManager::pathForSongFolder(int songID) {
    return ""_spr;
    std::string original = MusicDownloadManager::pathForSongFolder(songID);
    log::debug("songs: {}", original);
    if(original == "songs/") original = ""_spr;
    log::debug("songs2: {}", original);

    return original;
}