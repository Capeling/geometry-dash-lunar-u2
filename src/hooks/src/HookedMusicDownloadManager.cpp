#include "../headers/HookedMusicDownloadManager.h"

gd::string HookedMusicDownloadManager::pathForSFXFolder(int sfxID) {
    std::string original = MusicDownloadManager::pathForSFXFolder(sfxID);

    if(original == "sfx/") original = "/"_spr;

    return original;
}

gd::string HookedMusicDownloadManager::pathForSongFolder(int songID) {
    std::string original = MusicDownloadManager::pathForSongFolder(songID);

    if(original == "songs/") original = "/"_spr;

    return original;
}