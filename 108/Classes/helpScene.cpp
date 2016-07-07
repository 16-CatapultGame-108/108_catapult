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

	auto background2 = Sprite::create("background2.jpg");
	background2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background2, 0);

	auto label1 = Label::createWithTTF("this is help message", "fonts/arial.ttf", 50);
	label1->setColor(Color3B::RED);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(label1, 1);

	auto change = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(helpScene::return2home, this));
	auto menutoggle2 = Menu::create(change, NULL);
	menutoggle2->setPosition(Director::getInstance()->getVisibleSize().width * 0.8, Director::getInstance()->getVisibleSize().height * 0.8);
	this->addChild(menutoggle2, 1);

	return true;
}

void helpScene::return2home(Ref *ref) {
	this->stopAllActions();
	auto scene = MainPage::createScene();
	Director::getInstance()->replaceScene(scene);
}
