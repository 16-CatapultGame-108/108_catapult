#include "MainPageScene.h"
#include "Setting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene() {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Setting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Setting::init() {
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background3 = Sprite::create("background3.jpg");
	background3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background3, 0);

	auto change = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(Setting::return2home, this));
	auto menutoggle2 = Menu::create(change, NULL);
	menutoggle2->setPosition(Director::getInstance()->getVisibleSize().width * 0.85, Director::getInstance()->getVisibleSize().height * 0.8);
	this->addChild(menutoggle2, 1);

	#pragma execution_character_set("utf-8") 
	auto label1 = Label::createWithTTF("背景音乐：", "fonts/DFYuanW7-GB2312.ttf", 50);
	label1->setColor(Color3B::GREEN);
	label1->setPosition(Vec2(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 3 / 5));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF("音效：", "fonts/DFYuanW7-GB2312.ttf", 50);
	label2->setColor(Color3B::GREEN);
	label2->setPosition(Vec2(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 2 / 5));
	this->addChild(label2, 1);

	ControlSlider* slider = ControlSlider::create("bgFile.jpg", "progressFile.jpg", "thumbFile.jpg");
	slider->setPosition(Vec2(visibleSize.width * 3 / 5 + origin.x, visibleSize.height * 3 / 5 + origin.y));
	//设置滑动条的范围  
	slider->setMinimumValue(-15);
	slider->setMaximumValue(115);
	slider->setMaximumAllowedValue(100);
	slider->setMinimumAllowedValue(0);
	//设置滑动条当前值  
	slider->setValue(70);
	slider->addTargetWithActionForControlEvents(this, cccontrol_selector(Setting::sliderChange), Control::EventType::VALUE_CHANGED);
	this->addChild(slider, 1);

	ControlSlider* slider2 = ControlSlider::create("bgFile.jpg", "progressFile.jpg", "thumbFile.jpg");
	slider2->setPosition(Vec2(visibleSize.width * 3 / 5 + origin.x, visibleSize.height * 2 / 5 + origin.y));
	//设置滑动条的范围  
	slider2->setMinimumValue(-15);
	slider2->setMaximumValue(115);
	slider2->setMaximumAllowedValue(100);
	slider2->setMinimumAllowedValue(0);
	//设置滑动条当前值  
	slider2->setValue(70);
	slider2->addTargetWithActionForControlEvents(this, cccontrol_selector(Setting::sliderChange2), Control::EventType::VALUE_CHANGED);
	this->addChild(slider2, 1);

	return true;
}

void Setting::return2home(Ref *ref) {
	this->stopAllActions();
	Director::getInstance()->popScene();
}

void Setting::sliderChange(Ref* psender, Control::EventType event)
{
	ControlSlider* slider = (ControlSlider*)psender;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(slider->getValue() / 100);
}

void Setting::sliderChange2(Ref* psender, Control::EventType event)
{
	ControlSlider* slider = (ControlSlider*)psender;
	SimpleAudioEngine::getInstance()->setEffectsVolume(slider->getValue() / 100);
}