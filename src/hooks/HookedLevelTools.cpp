#include <hooks/HookedLevelTools.h>

using namespace geode::prelude;

bool HookedLevelTools::verifyLevelIntegrity(gd::string verifyString, int levelID) {
    return true;
}

gd::string HookedLevelTools::getAudioTitle(int audioID) {
    switch(audioID) {
        case 40: return "Active";
        case 41: return "ThunderZone";
        case 42: return "Earthsplitter";
        case 43: return "Space Battle";
        case 44: return "Power Glove";
        case 45: return "Payback";
        case 46: return "Hypercharged";
        case 47: return "Reverie";
        case 48: return "Ground Zero";
        case 49: return "Ultrasonic";
        default: return LevelTools::getAudioTitle(audioID);
    }
}

gd::string HookedLevelTools::getAudioFileName(int audioID) {
    if(audioID == 49) return "Ultrasonic.mp3"_spr;
    switch(audioID) {
        case 40: return "Active.mp3"_spr; //active
        case 41: return "ThunderZone.mp3"_spr; //thunderzone
        case 42: return "Earthsplitter.mp3"_spr; //earthsplitter
        case 43: return "SpaceBattle.mp3"_spr; //space battle
        case 44: return "PowerGlove.mp3"_spr; //power glove
        case 45: return "Payback.mp3"_spr; //payback
        case 46: return "Hypercharged.mp3"_spr; //hypercharged
        case 47: return "Reverie.mp3"_spr; //reverie
        case 48: return "GroundZero.mp3"_spr; //ground zero
        case 49: return "Ultrasonic.mp3"_spr; //Ultrasonic
        default: return LevelTools::getAudioFileName(audioID);
    }
}

gd::string HookedLevelTools::nameForArtist(int artistID) {
    switch(artistID) {
        case 12: return "Xtrullor";
        default: return LevelTools::nameForArtist(artistID);
    }
}

gd::string HookedLevelTools::urlForAudio(int audioID) {
    switch(audioID) {
        case 40: return "https://www.youtube.com/watch?v=_8cfes15DIk"; //active
        case 41: return "https://www.youtube.com/watch?v=oIu1o536GmI"; //thunderzone
        case 42: return "https://www.youtube.com/watch?v=sGF4mH4MeDo"; //earthsplitter
        case 43: return "https://www.youtube.com/watch?v=aZ5rMQIu1gc"; //space battle
        case 44: return "https://www.youtube.com/watch?v=ph7-CUy8OkE"; //power glove
        case 45: return "https://www.youtube.com/watch?v=391Q9i0yOXI"; //payback
        case 46: return "https://www.youtube.com/watch?v=4928RxhPtaE"; //hypercharged
        case 47: return "https://www.youtube.com/watch?v=sCTmeXavyhg"; //reverie
        case 48: return "https://www.youtube.com/watch?v=o0p9do2JO9c"; //ground zero
        case 49: return "https://www.youtube.com/watch?v=QF9MWwN6Pio"; //ultrasonic

        default: return LevelTools::urlForAudio(audioID);
    }
}

gd::string HookedLevelTools::ngURLForArtist(int artistID) {
    switch(artistID) {
        case 12: return "https://xtrullor.newgrounds.com/";
        default: return LevelTools::ngURLForArtist(artistID);
    }
}

gd::string HookedLevelTools::ytURLForArtist(int artistID) {
    switch(artistID) {
        case 12: return "https://www.youtube.com/@xtrullor";
        default: return LevelTools::ytURLForArtist(artistID);
    }
}

gd::string HookedLevelTools::fbURLForArtist(int artistID) {
    switch(artistID) {
        case 12: return "https://www.facebook.com/xtrullorofficial/";
        default: return LevelTools::fbURLForArtist(artistID);
    }
}

int HookedLevelTools::artistForAudio(int audioID) {
    switch(audioID) {
        case 40: return 0;
        case 41: return 1;
        case 42: return 12;
        case 43: return 6;
        case 44: return 6;
        case 45: return 0;
        case 46: return 5;
        case 47: return 12;
        case 48: return 8;
        case 49: return 0;
        default: return LevelTools::artistForAudio(audioID);
    }
}

GJGameLevel* HookedLevelTools::getLevel(int levelID, bool loaded) {
    GJGameLevel* level = GJGameLevel::create();

    switch(levelID) {
        case 1: 
            setLevelInfo(level, 2, GJDifficulty::Hard, 0, 16328); //active
            level->m_levelName = getAudioTitle(40);
            level->m_audioTrack = 40;
            level->m_coins = 3;
            break;
        case 2:
            setLevelInfo(level, 3, GJDifficulty::Hard, 0, 16965); //thunderzone
            level->m_levelName = getAudioTitle(41);
            level->m_audioTrack = 41;
            level->m_coins = 3;
            break;
        case 3:
            setLevelInfo(level, 4, GJDifficulty::Harder, 0, 19858); //earthsplitter
            level->m_levelName = getAudioTitle(42);
            level->m_audioTrack = 42;
            level->m_coins = 3;
            break;
        case 4:
            setLevelInfo(level, 6, GJDifficulty::Insane, 0, 18787); //space battle
            level->m_levelName = getAudioTitle(43);
            level->m_audioTrack = 43;
            level->m_coins = 3;
            break;
        case 5:
            setLevelInfo(level, 6, GJDifficulty::Harder, 0, 15851); //power glove
            level->m_levelName = getAudioTitle(44);
            level->m_audioTrack = 44;
            level->m_coins = 3;
            break;
        case 6:
            setLevelInfo(level, 7, GJDifficulty::Harder, 0, 16538); //payback
            level->m_levelName = getAudioTitle(45);
            level->m_audioTrack = 45;
            level->m_coins = 3;
            break;
        case 7:
            setLevelInfo(level, 8, GJDifficulty::Insane, 0, 18076); //hyperchanged
            level->m_levelName = getAudioTitle(46);
            level->m_audioTrack = 46;
            level->m_coins = 3;
            break;
        case 8:
            setLevelInfo(level, 9, GJDifficulty::Insane, 0, 18180); //reverie
            level->m_levelName = getAudioTitle(47);
            level->m_audioTrack = 47;
            level->m_coins = 3;
            break;
        case 9:
            setLevelInfo(level, 10, GJDifficulty::Insane, 0, 0); //ground zero
            level->m_levelName = getAudioTitle(48);
            level->m_audioTrack = 48;
            level->m_coins = 3;
            break;
        case 10:
            setLevelInfo(level, 11, GJDifficulty::Demon, 15, 27506); //ultrasonic
            level->m_levelName = getAudioTitle(49);
            level->m_audioTrack = 49;
            level->m_coins = 3;
            break;
        case 6001:
            setLevelInfo(level, 3, GJDifficulty::Hard, 0, 0);
            level->m_levelName = "Ancient Ruins";
            level->m_coins = 3;
            level->m_levelLength = 5;
            break;
    }
    if (!loaded) {
        level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);
    }
    level->m_levelID = levelID;
    level->m_levelType = GJLevelType::Local;
    return level;
}

void HookedLevelTools::setLevelInfo(GJGameLevel* level, int stars, GJDifficulty difficulty, int coinsRequired, int frameTime) {
    level->m_stars = stars;
    level->m_difficulty = difficulty;
    level->m_requiredCoins = coinsRequired;
    level->m_timestamp = frameTime;
}