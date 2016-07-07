#include "MainPageScene.h"
#include "helpScene.h"
#include "ChooseLevel.h"

USING_NS_CC;

Scene* MainPage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainPage::create();

    // add layer as a child to scene
    scene->addChild(layer);

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
    
	auto background = Sprite::create("background1.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	auto label1 = Label::createWithTTF("OVER WATCH", "fonts/arial.ttf", 100);
	label1->setColor(Color3B::GREEN);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 3 * visibleSize.height / 4));
	this->addChild(label1, 1);

	auto tem = Label::createWithTTF("Menu", "fonts/arial.ttf", 30);
	auto start = MenuItemImage::create("start1.png", "start2.png", CC_CALLBACK_1(MainPage::startscene, this));
	auto help = MenuItemImage::create("help1.png", "help2.png", CC_CALLBACK_1(MainPage::helpscene, this));
	auto menutoggle = Menu::create(start, help, NULL);
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * 0.5, Director::getInstance()->getVisibleSize().height * 0.4);
	menutoggle->alignItemsVerticallyWithPadding(tem->getContentSize().height / 3);
	this->addChild(menutoggle, 1);

	return true;
}

void MainPage::helpscene(Ref *ref) {
	this->stopAllActions();
	auto scene = helpScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainPage::startscene(Ref *ref) {
	this->stopAllActions();
	auto scene = ChooseLevel::createScene();
	Director::getInstance()->replaceScene(scene);
}
