#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>

class $modify(HookedLevelTools, LevelTools) {
    $override
    static bool verifyLevelIntegrity(gd::string levelString, int levelID);

    $override
    static gd::string getAudioTitle(int audioID);

    $override
    static gd::string getAudioFileName(int audioID);

    $override
    static gd::string nameForArtist(int artistID);

    $override
    static int artistForAudio(int audioID);

    $override
    static gd::string urlForAudio(int audioID);

    $override
    static gd::string ngURLForArtist(int artistID);

    $override
    static gd::string ytURLForArtist(int artistID);

    $override
    static gd::string fbURLForArtist(int artistID);

    $override
    static GJGameLevel* getLevel(int levelID, bool _save);

    static void setLevelInfo(GJGameLevel* level, int stars, GJDifficulty difficulty, int coinsRequired, int frameTime);
};