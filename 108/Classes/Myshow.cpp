#include "Myshow.h"
#include <string>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;


Scene* Myshow::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Myshow::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


void Myshow::Schedule_(){
	schedule(schedule_selector(Myshow::updateTime), 0.1f);
}

void Myshow::updateTime(float dt){
	totalTime -= dt;
	char t[10];
	sprintf(t, "%.0f", totalTime);
	time->setString(t);
}




void Myshow::playEffect(std::string s)
{
	SimpleAudioEngine::getInstance()->playEffect(s.c_str());
}

void Myshow::hurtplayer(float a) {
	float temp = blood->getPercentage();
	temp -= a;
	blood->setPercentage(temp);
	if (temp < 1) {
		//game over
	}
}


// on "init" you need to initialize your instance
bool Myshow::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//time
	time = Label::createWithBMFont("fonts/futura-48.fnt", "60");
	time->setColor(Color3B::RED);
	time->setPosition(visibleSize.width / 2, visibleSize.height - time->getContentSize().height);
	this->addChild(time, 1);

	totalTime = 60;
	Schedule_();

	//background
	Sprite* bg = Sprite::create("Myshow/bg.jpg");
	float oddsY = bg->getContentSize().height / visibleSize.height;
	float odds = bg->getContentSize().width / visibleSize.width;
	bg->setScaleY(1 / oddsY);
	bg->setScaleX(1 / odds);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg, 0);

	//player blood
	auto progressSprite = Sprite::create("Myshow/blood.jpg");
	blood = ProgressTimer::create(progressSprite);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setMidpoint(ccp(0, 0.5));
	blood->setBarChangeRate(ccp(1, 0));
	blood->setPercentage(100);
	//blood->runAction(RepeatForever::create(ProgressFromTo::create(3, 0, 100)));
	blood->setPosition(120, visibleSize.height - 50);
	addChild(blood, 0);

   
    
    return true;
}

