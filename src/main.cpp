#include "defs/all.h"
#include "defs/utils.h"
#include <Geode/modify/SongCell.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/SongsLayer.hpp>

class $modify(GameManager) {
	gd::string sheetNameForIcon(int iconID, int iconType) {
		if(iconID == 2 && iconType == 5) { //robot is weird if i dont do it like this
			return "robot_02"_spr;
		}
		auto ret = GameManager::sheetNameForIcon(iconID, iconType);
		return ret;
	}
};
 
class $modify(EditorPauseLayerExt, EditorPauseLayer) {
    bool init(LevelEditorLayer* editorLayer) {
        if(!EditorPauseLayer::init(editorLayer)) 
            return false;

        auto copySpr = ButtonSprite::create("Copy\nString", 50, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 0.4f);
        copySpr->setScale(0.8);

        auto copyBtn = CCMenuItemSpriteExtra::create(copySpr, this, menu_selector(EditorPauseLayerExt::onCopyString));

        auto actionsMenu = this->getChildByID("actions-menu");

        auto settingsMenu = this->getChildByID("settings-menu");
        settingsMenu->setPositionY(CCDirector::sharedDirector()->getScreenTop() - 25);
        
        actionsMenu->addChild(copyBtn);
        actionsMenu->updateLayout();
        return true;
    }
    void onCopyString(CCObject*) {
        auto levelString = m_editorLayer->m_level->m_levelString.c_str();
        clipboard::write(levelString);
    }
};

class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		log::info("time: {}", MBO(int, level, 0x414));
		return PlayLayer::init(level, useReplay, dontCreateObjects);
	}
};

class $modify(EditorUI) {
	void setupCreateMenu() {
		EditorUI::setupCreateMenu();
    	auto m_tab8 = (EditButtonBar*)this->m_createButtonBars->objectAtIndex(8);
    	m_tab8->m_buttonArray->insertObject(getCreateBtn(142, 4), 1);

		auto* GM = GameManager::sharedState();

		int rowCount = GM->getIntGameVariable("0049");
    	int columnCount = GM->getIntGameVariable("0050");

		m_tab8->reloadItems(rowCount, columnCount);
	}
};

void patchLevelsWin(int levels, int levelStart) {
	std::vector<unsigned char> levelsBytes = PatchTool::intToBytes(levelStart + levels);
	std::vector<unsigned char> levelStartByte = PatchTool::intToBytes(levelStart);
	std::vector<unsigned char> songBytes = PatchTool::intToBytes(39 + levels);
	PatchTool::patch(0x2680bf, {0xbe, levelStartByte[0], 0x00, 0x00, 0x00});
	PatchTool::patch(0x26812e, {levelsBytes[0]});
	PatchTool::patch(0x268386, {0x83, 0xfe, levelsBytes[0]});
	PatchTool::patch(0x26838b, {0x6a, PatchTool::intToBytes((levelStart + levels) - 1)[0]});
	PatchTool::patch(0x268398, {0x6a, levelsBytes[0]});

	PatchTool::patch(0x92283, {0xba, songBytes[0], 0x00, 0x00, 0x00});
    PatchTool::patch(0x92276, {0x83, 0xf8, songBytes[0]});
    PatchTool::patch(0x922c2, {0xba, songBytes[0], 0x00, 0x00, 0x00});
}

void patchLevelsA64() {
	PatchTool::patch(0x774BA8, {0x7f, 0x2e, 0x00, 0x71});
	PatchTool::patch(0x80B34C, {0x3f, 0xc4, 0x00, 0x71});
	PatchTool::patch(0x80B324, {0x3f, 0xc4, 0x00, 0x71});
	PatchTool::patch(0x80b328, {0x23, 0x06, 0x80, 0x52});
}

void patchLevelsA32() {
	PatchTool::patch(0x3F161E, {0xba, 0xf1, 0x0b, 0x0f});
	PatchTool::patch(0x44241E, {0x31, 0x29});
	PatchTool::patch(0x442400, {0x31, 0x29});
	PatchTool::patch(0x44240C, {0x31, 0x21});
}

void patchSongsLayerWin() {
	PatchTool::patch(0x38c141, {0xc7, 0x40, 0x34, 0x28});
	// Thunderzone
	PatchTool::patch(0x38c18f, {0xc7, 0x40, 0x34, 0x29});
	// Earthsplitter
	PatchTool::patch(0x38c1de, {0xc7, 0x40, 0x34, 0x2a});
	// Space Battle
	PatchTool::patch(0x38c22d, {0xc7, 0x40, 0x34, 0x2b});
	// Power Glove
	PatchTool::patch(0x38c27c, {0xc7, 0x40, 0x34, 0x2c});
	// Payback
	PatchTool::patch(0x38c2cb, {0xc7, 0x40, 0x34, 0x2d});
	// Hypercharged
	PatchTool::patch(0x38c31a, {0xc7, 0x40, 0x34, 0x2e});
	// Reverie
	PatchTool::patch(0x38c369, {0xc7, 0x40, 0x34, 0x2f});
	// Ground Zero
	PatchTool::patch(0x38c3b8, {0xc7, 0x40, 0x34, 0x30});
	// Balancer
	PatchTool::patch(0x38c407, {0xc7, 0x40, 0x34, 0x31});

	// Get rid of the other default songs from SongsLayer
	// Clutterfunk *
	PatchTool::patch(0x38c466, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// TOE *
	PatchTool::patch(0x38c4b5, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Electroman *
	PatchTool::patch(0x38c504, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Clubstep *
	PatchTool::patch(0x38c553, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Electrodynamix *
	PatchTool::patch(0x38c5a2, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Hexagon Force *
	PatchTool::patch(0x38c5f1, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Blast Processing *
	PatchTool::patch(0x38c640, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// TOE2 *
	PatchTool::patch(0x38c68f, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Geometrical *
	PatchTool::patch(0x38c6de, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Deadlocked *
	PatchTool::patch(0x38c72d, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Fingerdash *
	PatchTool::patch(0x38c77c, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// Dash *
	PatchTool::patch(0x38c7cb, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
}

$on_mod(Loaded) {
	#ifdef GEODE_IS_WINDOWS
	patchLevelsWin(10, 1);
	patchSongsLayerWin();
	Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x23b7ef), { 0x90, 0x90, 0x90, 0x90, 0x90 });
	Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x23bdd3), { 0x90, 0x90, 0x90, 0x90, 0x90 });
	#endif

	#ifdef GEODE_IS_ANDROID64
	patchLevelsA64();
	#endif

	#ifdef GEODE_IS_ANDROID32
	patchLevelsA32();
	#endif
}

class $modify(SongCell) { //why is this in main? because i cant be fucked making new files for this small shit
	void loadFromObject(SongObject* object) {
		SongCell::loadFromObject(object);
		int audioID = 0;

		#ifndef GEODE_IS_ANDROID64
		audioID = MBO(int, object, 0x34);
		#endif

		#ifdef GEODE_IS_ANDROID64
		audioID = MBO(int, object, 0x38);
		#endif
		auto songLabel = getChildOfType<CCLabelBMFont>(m_mainLayer, 0);

		songLabel->setString(LevelTools::getAudioTitle(audioID).c_str()); //for some fucking reason hooking artistForAudio breaks this so i have to manually fix it.
		if(audioID == -1)
			songLabel->setScale(0.573);
	}
};

#ifdef GEODE_IS_ANDROID
class $modify(SongsLayer) {
	void customSetup() {
		CCArray* songObjectArray = CCArray::create();
		songObjectArray->addObject(SongObject::create(40));
		songObjectArray->addObject(SongObject::create(41));
		songObjectArray->addObject(SongObject::create(42));
		songObjectArray->addObject(SongObject::create(43));
		songObjectArray->addObject(SongObject::create(44));
		songObjectArray->addObject(SongObject::create(45));
		songObjectArray->addObject(SongObject::create(46));
		songObjectArray->addObject(SongObject::create(47));
		songObjectArray->addObject(SongObject::create(48));
		songObjectArray->addObject(SongObject::create(49));
		songObjectArray->addObject(SongObject::create(-1));

		m_listLayer->m_listView = CustomListView::create(songObjectArray, nullptr, 220.0, 356.0, 0, BoomListType::Song, 0.0);
		m_listLayer->addChild(m_listLayer->m_listView);
	}
};
#endif

/*$execute {
	#ifdef GEODE_IS_WINDOWS
	Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x276452), {0x6a, 0x19});
    Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x27645b), {0x6a, 0x19});
	#endif
}*/