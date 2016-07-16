#include "MainPageScene.h"
#include "helpScene.h"
#include "ChooseLevel.h"
#include "SimpleAudioEngine.h"
#include "setting.h"
#include "Myshow.h"

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

	auto background = Sprite::create("Mainpage/background1.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);
	
	SimpleAudioEngine::getInstance()->preloadEffect("music/player_skill.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3",true);

	#pragma execution_character_set("utf-8") 
	auto label1 = Label::createWithTTF("ÊØÍûÏÈ·æ", "fonts/DFYuanW7-GB2312.ttf", 80);
	label1->setColor(Color3B::GREEN);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 3 * visibleSize.height / 4));
	this->addChild(label1, 1);

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

	auto Frame1 = SpriteFrame::create("animate/1.png", Rect(0, 0, 425, 281));
	auto Frame2 = SpriteFrame::create("animate/2.png", Rect(0, 0, 425, 281));
	auto Frame3 = SpriteFrame::create("animate/3.png", Rect(0, 0, 425, 281));
	auto Frame4 = SpriteFrame::create("animate/4.png", Rect(0, 0, 425, 281));
	auto Frame5 = SpriteFrame::create("animate/5.png", Rect(0, 0, 425, 281));
	auto Frame6 = SpriteFrame::create("animate/6.png", Rect(0, 0, 425, 281));
	auto Frame7 = SpriteFrame::create("animate/7.png", Rect(0, 0, 425, 281));
	auto Frame8 = SpriteFrame::create("animate/8.png", Rect(0, 0, 425, 281));
	auto Frame9 = SpriteFrame::create("animate/9.png", Rect(0, 0, 425, 281));
	auto Frame10 = SpriteFrame::create("animate/10.png", Rect(0, 0, 425, 281));
	auto Frame11 = SpriteFrame::create("animate/11.png", Rect(0, 0, 425, 281));
	auto Frame12 = SpriteFrame::create("animate/12.png", Rect(0, 0, 425, 281));
	auto Frame13 = SpriteFrame::create("animate/13.png", Rect(0, 0, 425, 281));
	auto Frame14 = SpriteFrame::create("animate/14.png", Rect(0, 0, 425, 281));
	auto Frame15 = SpriteFrame::create("animate/15.png", Rect(0, 0, 425, 281));
	auto Frame16 = SpriteFrame::create("animate/16.png", Rect(0, 0, 425, 281));
	auto Frame17 = SpriteFrame::create("animate/17.png", Rect(0, 0, 425, 281));
	auto Frame18 = SpriteFrame::create("animate/18.png", Rect(0, 0, 425, 281));
	auto sprite = Sprite::createWithSpriteFrame(Frame1);
	sprite->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.5, Director::getInstance()->getVisibleSize().height * 0.35));
	addChild(sprite,0);

	Vector<SpriteFrame*> Frames(18);
	Frames.pushBack(Frame1);
	Frames.pushBack(Frame2);
	Frames.pushBack(Frame3);
	Frames.pushBack(Frame4);
	Frames.pushBack(Frame5);
	Frames.pushBack(Frame6);
	Frames.pushBack(Frame7);
	Frames.pushBack(Frame8);
	Frames.pushBack(Frame9);
	Frames.pushBack(Frame10);
	Frames.pushBack(Frame11);
	Frames.pushBack(Frame12);
	Frames.pushBack(Frame13);
	Frames.pushBack(Frame14);
	Frames.pushBack(Frame15);
	Frames.pushBack(Frame16);
	Frames.pushBack(Frame17);
	Frames.pushBack(Frame18);

	auto animation = Animation::createWithSpriteFrames(Frames, 0.1);
	auto animate = Animate::create(animation);
	//auto move = MoveTo::create(.1f, Vec2(Director::getInstance()->getVisibleSize().width * 0.8, Director::getInstance()->getVisibleSize().height * 0.15));
	auto rotate = RotateBy::create(1.8f,10.0f);
	auto seq = Spawn::createWithTwoActions(animate,rotate);
	sprite->runAction(RepeatForever::create(seq));

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
