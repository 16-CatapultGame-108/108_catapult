#include "pause.h"
#include "MainPageScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* pause::createScene(RenderTexture* sqr) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = pause::create();

	// add layer as a child to scene
	scene->addChild(layer);

	auto background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	background->setPosition(Director::getInstance()->getVisibleSize().width * 0.5, Director::getInstance()->getVisibleSize().height * 0.5);
	background->setColor(Color3B::GRAY);
	background->setFlipY(true);
	scene->addChild(background,-1);
	// return the scene
	return scene;
}

bool pause::init() {
	if (!Layer::init())
	{
		return false;
	}

	auto return2home = MenuItemImage::create("pause/return2home1.png", "pause/return2home2.png", CC_CALLBACK_1(pause::return2home, this));
	auto replay = MenuItemImage::create("pause/replay1.png", "pause/replay2.png", CC_CALLBACK_1(pause::replay, this));
	auto resume = MenuItemImage::create("pause/resume1.png", "pause/resuem2.png", CC_CALLBACK_1(pause::resume, this));
	auto menutoggle = Menu::create(resume,replay,return2home, NULL);
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * .5, Director::getInstance()->getVisibleSize().height * 0.5);
	menutoggle->alignItemsVerticallyWithPadding(30);
	this->addChild(menutoggle, 2);

	return true;
}

void pause::return2home(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
		float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
	}
}

void pause::replay(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
		float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
	}
}

void pause::resume(Ref *ref) {
	Director::getInstance()->popScene();
}
