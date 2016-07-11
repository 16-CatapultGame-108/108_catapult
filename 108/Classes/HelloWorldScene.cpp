#include "HelloWorldScene.h"
#include "MainPageScene.h"

#include <math.h>
#define POWER_LIMIT 3.0
#define MIN_POWER 1.0
#define SHELL 5
#define POWER_RATE 100
#define DIS_PLAYER 80
using namespace std;


HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{
}

Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0, -200));
	auto layer = HelloWorld::create(scene->getPhysicsWorld());
	scene->addChild(layer, 1);
	return scene;
}

HelloWorld* HelloWorld::create(PhysicsWorld* world)
{
	HelloWorld* pRet = new HelloWorld();
	if (pRet && pRet->init(world))
	{
		return pRet;
	}
	pRet = NULL;
	return NULL;
}


void HelloWorld::testKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event){
		if (code == EventKeyboard::KeyCode::KEY_A) pressA(); 
		if (code == EventKeyboard::KeyCode::KEY_W) pressW();
		if (code == EventKeyboard::KeyCode::KEY_SPACE) pressspace();
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event){
		/*if (code == EventKeyboard::KeyCode::KEY_A)
		{
		player->setPosition(400, 400);
		}*/
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}



// on "init" you need to initialize your instance
bool HelloWorld::init(PhysicsWorld* world)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	m_world = world;
	dispatcher = Director::getInstance()->getEventDispatcher();
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//playBgm();


	//bound
	Node* bound = Node::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(visibleSize);
	boundBody->setDynamic(false);
	bound->setPhysicsBody(boundBody);
	bound->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bound, 2);

	//floor
	Node* bd = Node::create();
	PhysicsBody* bBody = PhysicsBody::createEdgeSegment(Vec2(0, 45), Vec2(visibleSize.width, 45));
	bBody->setDynamic(false);
	bd->setPhysicsBody(bBody);
	addChild(bd, 2);



	//player
	player = Sprite::create("HelloWorld/0.png");
	player->setPhysicsBody(PhysicsBody::createBox(player->getContentSize()));
	player->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	//player->getPhysicsBody()->setCollisionBitmask(0x00000000);
	player->setTag(1);
	player->setPosition(120, 50 + player->getContentSize().height / 2);
	this->addChild(player, 2);

	//test keyboard
	testKeyboardEvent();

	testMouseEvent(); //鼠标发射炮弹
	this->scheduleUpdate();//调度器


	//add Myshow layer
	myshow = new Myshow();
	myshow->init();
	addChild(myshow, 0);
	return true;
}


void HelloWorld::pressA() {
	if (flagA) {
		/*auto a = MoveBy::create(2, Point(-30, 0));
		player->runAction(a);
		flagA = false;*/
		this->stopAllActions();
		Director::getInstance()->replaceScene(MainPage::createScene());
	}
}

void HelloWorld::pressW() {
	if (player->getPosition().y - 2 <= (50 + player->getContentSize().height / 2)) {
		flagW = true;
	}
	if (flagW) {
		player->getPhysicsBody()->setVelocity(Vec2(0, 100));
		flagW = false;
	}
}


void HelloWorld::pressspace() {
	myshow->playEffect("music/player_skill.mp3");
}

double power = MIN_POWER;
//ProgressTimer* pro1;
void HelloWorld::testMouseEvent()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [&](Event* event){
		mousedown = true;

		Sprite*bg1 = Sprite::create("HelloWorld/bar.png");
		pro1 = ProgressTimer::create(bg1);
		pro1->setPosition(ccp(130, 100));
		pro1->setAnchorPoint(Vec2(0, 0.5));
		//pro1->setRotation(40.0f);
		this->addChild(pro1);

		//条形，定义进度条方式：从右到左显示
		pro1->setType(kCCProgressTimerTypeBar);
		pro1->setBarChangeRate(ccp(1, 0));
		pro1->setMidpoint(ccp(0, 0.5));
		//pro1->setReverseProgress(true); //反进度显示

	};
	listener->onMouseUp = [&](Event* event){
		mousedown = false;
		Launch(power);
		power = MIN_POWER;
		removeChild(pro1);
	};
	listener->onMouseMove = [&](Event* event){
		EventMouse* e = (EventMouse*)event;
		mouse_x = e->getCursorX();
		mouse_y = e->getCursorY();
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::update(float dt) {
	if (mousedown) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		int x = player->getPositionX(), y = player->getPositionY();
		if (!full) {
			power += dt;
			if (power >= POWER_LIMIT + MIN_POWER) full = true;
		}
		else {
			power -= dt;
			if (power <= MIN_POWER) full = false;
		}
		pro1->setPercentage((power - MIN_POWER) / POWER_LIMIT * 100);
		pro1->setPositionX(x);
		pro1->setPositionY(y);
		double diff_x = mouse_x - x, diff_y = visibleSize.height + mouse_y - y;
		double dt = atan2(diff_y, diff_x);
		pro1->setRotation(-dt * 180 / 3.14);
		//auto rotateTo = RotateTo::create(0.0f, 40.0f);
		//pro1->runAction(rotateTo);
	}

	/*
	else if (readyLaunch) {
	readyLaunch = false;
	}*/
}
void HelloWorld::Launch(double power) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (power > POWER_LIMIT) {
		power = POWER_LIMIT;
	}
	int x = player->getPositionX(), y = player->getPositionY();
	//log(x);
	double diff_x = mouse_x - x, diff_y = visibleSize.height + mouse_y - y;
	double dt = atan2(diff_y, diff_x);
	//log(dt);
	auto sp = Sprite::create("HelloWorld/stone.png");
	sp->setTag(SHELL);
	auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2, PhysicsMaterial(1.0f, 1.0f, 1.0f));
	//double z = sin(dt);
	//log(z);
	body->setVelocity(Vec2(cos(dt)*power * POWER_RATE, sin(dt)*power * POWER_RATE));
	//body->setGravityEnable(false);
	sp->setPhysicsBody(body);
	sp->setPositionX(x + cos(dt)*DIS_PLAYER);
	sp->setPositionY(y + sin(dt)*DIS_PLAYER);
	addChild(sp);
}



