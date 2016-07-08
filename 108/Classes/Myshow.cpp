#include "Myshow.h"
#include <string>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;


Myshow* Myshow::myshow = NULL;
Myshow* Myshow::getInstance() {
	if (myshow == NULL) {
		myshow = new Myshow();
		myshow->init();
	}
	return myshow;
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


void Myshow::preloadMusic()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/player_skill.mp3");
}


void Myshow::playBgm()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
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
	Sprite* bg = Sprite::create("1/bg.jpg");
	float oddsY = bg->getContentSize().height / visibleSize.height;
	float odds = bg->getContentSize().width / visibleSize.width;
	bg->setScaleY(1 / oddsY);
	bg->setScaleX(1 / odds);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg, 0);

	//player blood
	auto progressSprite = Sprite::create("blood.jpg");
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

