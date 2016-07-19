#include "MainPageScene.h"
#include "helpScene.h"
USING_NS_CC;

Scene* helpScene::createScene() {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = helpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool helpScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("HelpScene/background2.jpg");
	float oddsY = background->getContentSize().height / visibleSize.height;
	float odds = background->getContentSize().width / visibleSize.width;
	background->setScaleY(1 / oddsY);
	background->setScaleX(1 / odds);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, 0);

	auto message = Sprite::create("HelpScene/helpmessage.png");
	message->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	message->setScale(1.2);
	this->addChild(message);

	auto change = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(helpScene::return2home, this));
	auto menutoggle2 = Menu::create(change, NULL);
	menutoggle2->setPosition(Director::getInstance()->getVisibleSize().width * 0.85, Director::getInstance()->getVisibleSize().height * 0.8);
	this->addChild(menutoggle2, 1);

	return true;
}

void helpScene::return2home(Ref *ref) {
	this->stopAllActions();
	Director::getInstance()->popScene();
}
