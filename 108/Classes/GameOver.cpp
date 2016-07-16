#include "GameOver.h"
#include "MainPageScene.h"

USING_NS_CC;

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
		auto label = Label::createWithTTF("You win!", "fonts/DFYuanW7-GB2312.ttf", 80);
		label->setColor(Color3B::GREEN);
		label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
		scene->addChild(label, 1);
	}
	else {
		auto label = Label::createWithTTF("You lose!", "fonts/DFYuanW7-GB2312.ttf", 80);
		label->setColor(Color3B::GREEN);
		label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
		scene->addChild(label, 1);
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
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * .8, Director::getInstance()->getVisibleSize().height * 0.8);
	menutoggle->alignItemsVerticallyWithPadding(30);
	this->addChild(menutoggle, 2);

	return true;
}

void GameOver::return2home(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void GameOver::replay(Ref *ref) {
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}
