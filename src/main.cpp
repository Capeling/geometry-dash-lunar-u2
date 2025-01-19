#include <Geode/modify/SongCell.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/SongsLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <layers/VaultLayer.h>
#include <utils/patch.hpp>

using namespace geode::prelude;

class $modify(CCSprite) {
	static CCSprite* create(const char *pszFileName) {
		if(std::string_view(pszFileName) == std::string_view("dialogIcon_054.png")) {
			return CCSprite::create("GJL_lunarDialogue_001.png"_spr);
		}
		if(std::string_view(pszFileName) == std::string_view("dialogIcon_055.png")) {
			return CCSprite::create("GJL_secretLunar_001.png"_spr);
		}
		return CCSprite::create(pszFileName);
	}
};

class $modify(HookedEditorUI, EditorUI) {

	struct Fields {
		CCSprite* m_jumpscareSprite = nullptr;
		CCLayerColor* m_jumpscareBG = nullptr;
	};

	bool init(LevelEditorLayer* editorLayer) {
		bool init = EditorUI::init(editorLayer);
		if(init) {
			#ifndef DEBUG_ENABLED
			auto delay = CCDelayTime::create(0.2f);
        	auto func = CCCallFunc::create(this, callfunc_selector(HookedEditorUI::createJumpscare));
        	this->runAction(CCSequence::create(delay, func, 0));
			#endif
		}
		return init;
	}
	void createJumpscare() {
		m_fields->m_jumpscareBG = CCLayerColor::create({0, 0, 0, 255});
		m_fields->m_jumpscareSprite = CCSprite::createWithSpriteFrameName("jumpscare.png"_spr);
		m_fields->m_jumpscareSprite->setScale(0.1f);
		m_fields->m_jumpscareSprite->setPosition(CCDirector::get()->getWinSize() / 2);
		addChild(m_fields->m_jumpscareBG, 99999);
		addChild(m_fields->m_jumpscareSprite, 99999);

		auto scale = CCScaleTo::create(0.1f, 2.375f);
		auto ease = CCEaseInOut::create(scale, 2.f);
		auto audio = CCCallFunc::create(this, callfunc_selector(HookedEditorUI::playJumpAudio));
		auto delay = CCDelayTime::create(1.f);
		auto remove = CCCallFunc::create(this, callfunc_selector(HookedEditorUI::removeJumpscare));
		m_fields->m_jumpscareSprite->runAction(CCSequence::create(ease, audio, delay, remove, 0));
	}
	void removeJumpscare() {
		if(m_fields->m_jumpscareSprite) {
			m_fields->m_jumpscareSprite->removeFromParent();
		}
		if(m_fields->m_jumpscareBG) {
			m_fields->m_jumpscareBG->removeFromParent();
		}
	}
	void playJumpAudio() {
		FMODAudioEngine::sharedEngine()->playEffect("jumpscareAudio.mp3"_spr);
	}
};

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