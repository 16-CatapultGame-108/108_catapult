#include "HelloWorldScene.h"
#include "Myshow.h"


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
	player = Sprite::create("1/0.png");
	player->setPhysicsBody(PhysicsBody::createBox(player->getContentSize()));
	player->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	//player->getPhysicsBody()->setCollisionBitmask(0x00000000);
	player->setTag(1);
	player->setPosition(120, 50 + player->getContentSize().height / 2);
	this->addChild(player, 2);

	//test keyboard
	testKeyboardEvent();


	//add Myshow layer
	addChild(Myshow::getInstance(), 0);
	return true;
}


void HelloWorld::pressA() {
	if (flagA) {
		/*auto a = MoveBy::create(2, Point(-30, 0));
		player->runAction(a);
		flagA = false;*/
		Myshow::getInstance()->hurtplayer(10.0);
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
	Myshow::getInstance()->playEffect("music/player_skill.mp3");
}


