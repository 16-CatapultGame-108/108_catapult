#include "MainPageScene.h"
#include "helpScene.h"
#include "ChooseLevel.h"
#include "SimpleAudioEngine.h"
#include "setting.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainPage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainPage::create();
    // add layer as a child to scene
    scene->addChild(layer);

	Director::getInstance()->pushScene(scene);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainPage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	Sprite* background = Sprite::create("Mainpage/background1.jpg");
	float oddsY = background->getContentSize().height / visibleSize.height;
	float odds = background->getContentSize().width / visibleSize.width;
	background->setScaleY(1 / oddsY);
	background->setScaleX(1 / odds);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, 0);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm1.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/shoot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/skill.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/skill2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/skill3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/run.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3",true);
	
	Sprite* title = Sprite::create("Mainpage/title.png");
	title->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 3 * visibleSize.height / 4));
	title->setScale(1.5);
	this->addChild(title, 1);

	auto musicOnItem = MenuItemImage::create("Mainpage/laba1.png", "Mainpage/laba1.png");
	musicOnItem->setUserData((void *)"ON");
	auto musicOffItem = MenuItemImage::create("Mainpage/laba2.png", "Mainpage/laba2.png");
	musicOffItem->setUserData((void *)"OFF");
	auto menuToggle = MenuItemToggle::createWithCallback([](Ref* obj){
		MenuItemFont *item = (MenuItemFont*)((MenuItemToggle *)obj)->getSelectedItem();
		char* musicState = (char*)item->getUserData();
		if (musicState == "ON") {
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		else {
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}, musicOnItem, musicOffItem, NULL);
	menuToggle->setPosition(visibleSize.width - 200, 80);
	auto menu = Menu::create(menuToggle, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	auto end = MenuItemImage::create("Mainpage/end1.png", "Mainpage/end2.png", CC_CALLBACK_1(MainPage::closegame, this));
	auto endmenutoggle = Menu::create(end, NULL);
	endmenutoggle->setPosition(visibleSize.width - 100, 80);
	this->addChild(endmenutoggle, 1);

	auto tem = Label::createWithTTF("Menu", "fonts/arial.ttf", 30);
	auto start = MenuItemImage::create("Mainpage/start1.png", "Mainpage/start2.png", CC_CALLBACK_1(MainPage::startscene, this));
	auto help = MenuItemImage::create("Mainpage/help1.png", "Mainpage/help2.png", CC_CALLBACK_1(MainPage::helpscene, this));
	auto setting = MenuItemImage::create("Mainpage/setting1.png", "Mainpage/setting2.png", CC_CALLBACK_1(MainPage::setting, this));
	auto menutoggle = Menu::create(start, setting, help, NULL);
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * 0.5, Director::getInstance()->getVisibleSize().height * 0.35);
	menutoggle->alignItemsVerticallyWithPadding(tem->getContentSize().height / 3);
	this->addChild(menutoggle, 1);

	return true;
}

void MainPage::helpscene(Ref *ref) {
	this->stopAllActions();
	auto scene = helpScene::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(.5, scene));
}

void MainPage::startscene(Ref *ref) {
	this->stopAllActions();
	auto scene = ChooseLevel::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(.5, scene));
}

void MainPage::closegame(Ref *ref) {
	Director::getInstance()->end();
}

void MainPage::setting(Ref *ref) {
	this->stopAllActions();
	auto scene = Setting::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(.5, scene));
}
