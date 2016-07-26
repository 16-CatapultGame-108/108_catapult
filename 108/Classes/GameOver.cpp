#include "GameOver.h"
#include "MainPageScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameOver::createScene(RenderTexture* sqr, bool wol) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	auto background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	background->setPosition(Director::getInstance()->getVisibleSize().width * 0.5, Director::getInstance()->getVisibleSize().height * 0.5);
	background->setColor(Color3B::GRAY);
	background->setFlipY(true);
	scene->addChild(background, -1);

	if (wol) {
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
			float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/win.mp3", true);
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
		}
		auto s1 = Sprite::create("gameover/endwin.png");
		s1->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height * .7));
		scene->addChild(s1);
	}
	else {
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
			float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/lose.mp3", true);
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
		}
		auto s2 = Sprite::create("gameover/endlose.png");
		s2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height * .7));
		scene->addChild(s2);
	}
	// return the scene
	return scene;
}

bool GameOver::init() {
	if (!Layer::init())
	{
		return false;
	}

	auto return2home = MenuItemImage::create("pause/return2home1.png", "pause/return2home2.png", CC_CALLBACK_1(GameOver::return2home, this));
	auto replay = MenuItemImage::create("pause/replay1.png", "pause/replay2.png", CC_CALLBACK_1(GameOver::replay, this));
	auto menutoggle = Menu::create(replay, return2home, NULL);
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * .5, Director::getInstance()->getVisibleSize().height * 0.4);
	menutoggle->alignItemsVerticallyWithPadding(30);
	this->addChild(menutoggle, 2);

	return true;
}

void GameOver::return2home(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
		float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
	}
}

void GameOver::replay(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
		float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
	}
}
