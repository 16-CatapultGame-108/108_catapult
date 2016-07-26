#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define POWER_LIMIT 3.0
#define MIN_POWER 1.0
#define POWER_RATE 110
#define DIS_PLAYER 50

static int interval;
static int lasttime;
static int page;

Scene* HelloWorld::createScene(int t) {
	page = t;
	Scene* scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -255));
	auto layer = HelloWorld::create(scene->getPhysicsWorld());
	scene->addChild(layer, 1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (t == 1) {
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
			float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm1.mp3", true);
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
		}
		Sprite* background = Sprite::create("HelloWorld/background1.jpg");
		float oddsY = background->getContentSize().height / visibleSize.height;
		float odds = background->getContentSize().width / visibleSize.width;
		background->setScaleY(1 / oddsY);
		background->setScaleX(1 / odds);
		background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		scene->addChild(background, 0);
		interval = .5;
		lasttime = 60;
	} else {
		float tem = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm2.mp3", true);
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(tem);
		}
		Sprite* background = Sprite::create("HelloWorld/background2.jpg");
		float oddsY = background->getContentSize().height / visibleSize.height;
		float odds = background->getContentSize().width / visibleSize.width;
		background->setScaleY(1 / oddsY);
		background->setScaleX(1 / odds);
		background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		scene->addChild(background, 0);
		interval = .1;
		lasttime = 60;
	}
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

bool HelloWorld::init(PhysicsWorld* world)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto obstacle = Sprite::create("HelloWorld/obstacle.png");
	obstacle->setPosition(visibleSize.width / 2, obstacle->getContentSize().height / 2 + 50);
	this->addChild(obstacle, 1);
	PhysicsBody* obstacle_ = PhysicsBody::createBox(obstacle->getContentSize());
	obstacle_->setDynamic(false);
	Node* tem = Node::create();
	tem->setPhysicsBody(obstacle_);
	tem->setPosition(visibleSize.width / 2, obstacle->getContentSize().height / 2 + 50);
	tem->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	tem->setTag(1);
	this->addChild(tem, 1);
	
	//计时器
	time = Label::createWithBMFont("fonts/futura-48.fnt", "61");
	time->setColor(Color3B::ORANGE);
	time->setPosition(visibleSize.width / 2, visibleSize.height - time->getContentSize().height);
	this->addChild(time);
	totalTime = 60;
	schedule(schedule_selector(HelloWorld::updateTime), 0.1f);

	//边界
	Node* bound = Node::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(visibleSize);
	boundBody->setDynamic(false);
	bound->setPhysicsBody(boundBody);
	bound->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bound->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	bound->setTag(-1);
	this->addChild(bound);

	//地面
	Node* bd = Node::create();
	PhysicsBody* bBody = PhysicsBody::createEdgeSegment(Vec2(0, 50), Vec2(visibleSize.width, 50));
	bBody->setDynamic(false);
	bd->setPhysicsBody(bBody);
	bd->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	bd->setTag(1);
	addChild(bd);

	auto Frame1 = SpriteFrame::create("animate2/1.png", Rect(0, 0, 150, 172));
	player1 = Sprite::createWithSpriteFrame(Frame1);
	player1->setPosition(visibleSize.width / 8, 50 + player1->getContentSize().height / 2);
	player1->setPhysicsBody(PhysicsBody::createBox(player1->getContentSize(), PhysicsMaterial(100.0f, .0f, .0f)));
	health1 = 100;
	blackart1 = 100;
	player1->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	player1->setTag(2);
	this->addChild(player1);

	auto progressSprite1 = Sprite::create("HelloWorld/blood.jpg");
	blood1 = ProgressTimer::create(progressSprite1);
	blood1->setType(ProgressTimer::Type::BAR);
	blood1->setMidpoint(ccp(0, 0.5));
	blood1->setBarChangeRate(ccp(1, 0));
	blood1->setPercentage(100);
	blood1->setPosition(visibleSize.width * .3, visibleSize.height * .85);
	auto ba = Sprite::create("HelloWorld/back.jpg");
	ba->setPosition(visibleSize.width * .3, visibleSize.height * .85);
	addChild(ba);
	addChild(blood1);

	auto progressSprite1_ = Sprite::create("HelloWorld/magic.jpg");
	magic1 = ProgressTimer::create(progressSprite1_);
	magic1->setType(ProgressTimer::Type::BAR);
	magic1->setMidpoint(ccp(0, 0.5));
	magic1->setBarChangeRate(ccp(1, 0));
	magic1->setPercentage(100);
	magic1->setPosition(visibleSize.width * .3, visibleSize.height * .80);
	auto ba2 = Sprite::create("HelloWorld/back.jpg");
	ba2->setPosition(visibleSize.width * .3, visibleSize.height * .80);
	addChild(ba2);
	addChild(magic1);

	auto ali = Sprite::create("HelloWorld/ali.png");
	ali->setScale(.8);
	ali->setPosition(visibleSize.width * .1, visibleSize.height * .85);
	this->addChild(ali);

	if (page == 1) {
		auto monster = Sprite::create("HelloWorld/monster.png");
		monster->setScale(.7);
		monster->setPosition(visibleSize.width * .9, visibleSize.height * .85);
		this->addChild(monster);

		auto Frame1_ = SpriteFrame::create("animate/1.png", Rect(0, 0, 155, 160));
		player2 = Sprite::createWithSpriteFrame(Frame1_);
		player2->setPosition(visibleSize.width * 7 / 8, 50 + player2->getContentSize().height / 2);
		player2->setPhysicsBody(PhysicsBody::createBox(player2->getContentSize(), PhysicsMaterial(100.0f, .0f, .0f)));
		health2 = 100;
		blackart2 = 100;
		player2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		player2->setTag(3);
		this->addChild(player2);
	}
	if (page == 2) {
		auto monster = Sprite::create("HelloWorld/monster2.png");
		monster->setScale(.7);
		monster->setPosition(visibleSize.width * .9, visibleSize.height * .85);
		this->addChild(monster);
		//player2
		auto Frame1_ = SpriteFrame::create("animate/21.png", Rect(0, 0, 165, 160));
		player2 = Sprite::createWithSpriteFrame(Frame1_);
		player2->setPosition(visibleSize.width * 7 / 8, 50 + player2->getContentSize().height / 2);
		player2->setPhysicsBody(PhysicsBody::createBox(player2->getContentSize(), PhysicsMaterial(100.0f, .0f, .0f)));
		health2 = 100;
		blackart2 = 100;
		player2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		player2->setTag(3);
		this->addChild(player2);
	}

	auto progressSprite2 = Sprite::create("HelloWorld/blood.jpg");
	blood2 = ProgressTimer::create(progressSprite2);
	blood2->setType(ProgressTimer::Type::BAR);
	blood2->setMidpoint(ccp(0, 0.5));
	blood2->setBarChangeRate(ccp(1, 0));
	blood2->setPercentage(100);
	blood2->setPosition(visibleSize.width * .7, visibleSize.height * .85);
	auto ba_ = Sprite::create("HelloWorld/back.jpg");
	ba_->setPosition(visibleSize.width * .7, visibleSize.height * .85);
	addChild(ba_);
	addChild(blood2);

	auto progressSprite2_ = Sprite::create("HelloWorld/magic.jpg");
	magic2 = ProgressTimer::create(progressSprite2_);
	magic2->setType(ProgressTimer::Type::BAR);
	magic2->setMidpoint(ccp(0, 0.5));
	magic2->setBarChangeRate(ccp(1, 0));
	magic2->setPercentage(100);
	magic2->setPosition(visibleSize.width * .7, visibleSize.height * .80);
	auto ba2_ = Sprite::create("HelloWorld/back.jpg");
	ba2_->setPosition(visibleSize.width * .7, visibleSize.height * .80);
	addChild(ba2_);
	addChild(magic2);

	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event){
		auto Frame1 = SpriteFrame::create("animate2/1.png", Rect(0, 0, 150, 172));
		auto Frame2 = SpriteFrame::create("animate2/2.png", Rect(0, 0, 150, 172));
		auto Frame3 = SpriteFrame::create("animate2/3.png", Rect(0, 0, 150, 172));
		Vector<SpriteFrame*> Frames(3);
		Frames.pushBack(Frame1);
		Frames.pushBack(Frame2);
		Frames.pushBack(Frame3);
		auto animation = Animation::createWithSpriteFrames(Frames, 0.3 / 3);
		auto animate = Animate::create(animation);

		if (code == EventKeyboard::KeyCode::KEY_A) {
			SimpleAudioEngine::getInstance()->playEffect("music/run.wav");
			tools();
			auto moveleft = MoveTo::create(.3,Vec2(player1->getPositionX() - 50, player1->getPositionY()));
			auto seq = Spawn::createWithTwoActions(moveleft, animate);
			player1->runAction(seq);
		}
		if (code == EventKeyboard::KeyCode::KEY_D) {
			SimpleAudioEngine::getInstance()->playEffect("music/run.wav");
			tools();
			auto moveright = MoveTo::create(.3,Vec2(player1->getPositionX() + 50, player1->getPositionY()));
			auto seq = Spawn::createWithTwoActions(moveright, animate);
			player1->runAction(seq);
		}
		if (code == EventKeyboard::KeyCode::KEY_W){
			tools();
			if (player1->getPosition().y - 2 <= (50 + player1->getContentSize().height / 2)) {
				auto jump = MoveTo::create(.3, Vec2(player1->getPositionX(), player1->getPositionY() + 100));
				auto seq = Sequence::create(jump, NULL);
				player1->runAction(seq);
			}
		}
		if (code == EventKeyboard::KeyCode::KEY_SPACE) {
			tools();
			HelloWorld::pause(this);
		}
		if (code == EventKeyboard::KeyCode::KEY_Q) {
			if (page == 1) {
				auto Frame1 = SpriteFrame::create("animate/3.png", Rect(0, 0, 155, 160));
				auto Frame2 = SpriteFrame::create("animate/2.png", Rect(0, 0, 155, 160));
				Vector<SpriteFrame*> Frames(2);
				Frames.pushBack(Frame1);
				Frames.pushBack(Frame2);
				auto animation = Animation::createWithSpriteFrames(Frames, 0.4 / 2);
				auto animate = Animate::create(animation);
				auto seq = Sequence::create(animate, NULL);
				player2->runAction(seq);
			}
			if (page == 2) {
				auto Frame1 = SpriteFrame::create("animate/23.png", Rect(0, 0, 165, 160));
				auto Frame2 = SpriteFrame::create("animate/22.png", Rect(0, 0, 165, 160));
				Vector<SpriteFrame*> Frames(2);
				Frames.pushBack(Frame1);
				Frames.pushBack(Frame2);
				auto animation = Animation::createWithSpriteFrames(Frames, 0.4 / 2);
				auto animate = Animate::create(animation);
				auto seq = Sequence::create(animate, NULL);
				player2->runAction(seq);
			}
			tools();
			if (blackart1 >= 80) {
				blackart1 -= 80;
				magic1->setPercentage(blackart1);
				SimpleAudioEngine::getInstance()->playEffect("music/skill.wav");
				auto Frame1 = SpriteFrame::create("animate4/1.png", Rect(0, 0, 300, 500));
				auto Frame2 = SpriteFrame::create("animate4/2.png", Rect(0, 0, 300, 500));
				auto Frame3 = SpriteFrame::create("animate4/3.png", Rect(0, 0, 300, 500));
				auto Frame4 = SpriteFrame::create("animate4/4.png", Rect(0, 0, 300, 500));
				auto Frame5 = SpriteFrame::create("animate4/5.png", Rect(0, 0, 300, 500));
				auto Frame6 = SpriteFrame::create("animate4/6.png", Rect(0, 0, 300, 500));
				auto Frame7 = SpriteFrame::create("animate4/7.png", Rect(0, 0, 300, 500));
				auto Frame8 = SpriteFrame::create("animate4/8.png", Rect(0, 0, 300, 500));
				auto Frame9 = SpriteFrame::create("animate4/9.png", Rect(0, 0, 300, 500));
				auto s_sprite = Sprite::createWithSpriteFrame(Frame1);
				s_sprite->setPosition(player2->getPositionX() * 1.0, player2->getPositionY() * 1.0 + 20);
				addChild(s_sprite);
				Vector<SpriteFrame*> Frames(9);
				Frames.pushBack(Frame1);
				Frames.pushBack(Frame2);
				Frames.pushBack(Frame3);
				Frames.pushBack(Frame4);
				Frames.pushBack(Frame5);
				Frames.pushBack(Frame6);
				Frames.pushBack(Frame7);
				Frames.pushBack(Frame8);
				Frames.pushBack(Frame9);
				auto s_animation = Animation::createWithSpriteFrames(Frames, 0.1);
				auto s_animate = Animate::create(s_animation);
				auto seq = Sequence::create(s_animate,NULL);
				s_sprite->runAction(seq);
				health2 -= 30;
				blood2->setPercentage(health2);
				if (health2 <= 0) {
					gameOver();
				}
			}
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//准备发射
	prepare(); 
	this->scheduleUpdate();//调度器

	//碰撞检测
	auto listener2 = EventListenerPhysicsContact::create();
	listener2->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	return true;
}

double power = MIN_POWER;
void HelloWorld::prepare() {
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [&](Event* event){
		mousedown = true;
		Sprite*bg1 = Sprite::create("HelloWorld/bar.png");
		timer = ProgressTimer::create(bg1);
		timer->setPosition(ccp(130, 100));
		timer->setAnchorPoint(Vec2(0, .5));
		//timer->setRotation(40.0f);
		this->addChild(timer);
		//条形，定义进度条方式：从右到左显示
		timer->setType(kCCProgressTimerTypeBar);
		timer->setBarChangeRate(ccp(1, 0));
		timer->setMidpoint(ccp(0, 0.5));
		//timer->setReverseProgress(true); //反进度显示
		bar = Sprite::create("HelloWorld/bar2.png");
		bar->setAnchorPoint(Vec2(0, 0.5));
		this->addChild(bar);
	};
	listener->onMouseUp = [&](Event* event){
		mousedown = false;
		Launch(power);
		power = MIN_POWER;
		removeChild(timer);
		removeChild(bar);
	};
	listener->onMouseMove = [&](Event* event){
		EventMouse* e = (EventMouse*)event;
		mouse_x = e->getCursorX();
		mouse_y = e->getCursorY();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::Launch(double power) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (power > POWER_LIMIT) {
		power = POWER_LIMIT;
	}
	if (sp_) {
		return;
	}
 	int x = player1->getPositionX(), y = player1->getPositionY();
	//log(x);
	double diff_x = mouse_x - x, diff_y = visibleSize.height + mouse_y - y;
	double dt = atan2(diff_y, diff_x);
	//log(dt);
	sp = Sprite::create("HelloWorld/stone.png");
	auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2, PhysicsMaterial(3.0f, .0f, .0f));
	//double z = sin(dt);
	//log(z);
	body->setVelocity(Vec2(cos(dt)*power * POWER_RATE * 3, sin(dt)*power * POWER_RATE));
	//body->setGravityEnable(false);
	sp->setPhysicsBody(body);
	sp->setPositionX(x + cos(dt)*DIS_PLAYER);
	sp->setPositionY(y + sin(dt)*DIS_PLAYER);
	sp->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	sp->setTag(0);
	addChild(sp);
	sp_ = true;
	SimpleAudioEngine::getInstance()->playEffect("music/shoot.wav");
}

void HelloWorld::update(float dt) {
	if (mousedown) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		int x = player1->getPositionX(), y = player1->getPositionY();
		if (!full) {
			power += dt;
			if (power >= POWER_LIMIT + MIN_POWER) full = true;
		}
		else {
			power -= dt;
			if (power <= MIN_POWER) full = false;
		}
		timer->setPercentage((power - MIN_POWER) / POWER_LIMIT * 100);
		timer->setPositionX(x);
		timer->setPositionY(y);
		double diff_x = mouse_x - x, diff_y = visibleSize.height + mouse_y - y;
		double dt = atan2(diff_y, diff_x);
		timer->setRotation(-dt * 180 / 3.14);
		timer->setPositionX(x + cos(dt)*(DIS_PLAYER + 5));
		timer->setPositionY(y + sin(dt)*(DIS_PLAYER + 5));
		bar->setRotation(-dt * 180 / 3.14);
		bar->setPositionX(x + cos(dt)*DIS_PLAYER);
		bar->setPositionY(y + sin(dt)*DIS_PLAYER);
		//auto rotateTo = RotateTo::create(0.0f, 40.0f);
		//timer->runAction(rotateTo);
	}
}

void HelloWorld::updateTime(float temtime) {
	totalTime -= temtime;
	if (lasttime - totalTime >= interval) {
		simpleAI();
		lasttime = totalTime;
	}
	char mtime[10];
	sprintf(mtime, "%.0f", totalTime);
	time->setString(mtime);
	if (totalTime <= 0)
		gameOver();
}

void HelloWorld::pause(Ref *ref) {
	RenderTexture* sqr = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
	sqr->begin();
	// 访问当前运行屏幕 上的每个子结点
	Director::sharedDirector()->getRunningScene()->visit();
	// 结束绘制
	sqr->end();
	Director::getInstance()->pushScene(pause::createScene(sqr));
}

//边界-1 石头0 地面1 人物1-2 人物2-3 tool1-7 enemy子弹-8
bool HelloWorld::onContactBegan(PhysicsContact& contact) {
	Sprite* x1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* y1 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	int x2 = x1->getTag();
	int y2 = y1->getTag();
	if (x2 == -1 && y2 == 0 || x2 == 0 && y2 == -1) {
		sp_ = false;
		this->removeChild(sp);
	}

	if (x2 == 1 && y2 == 0 || x2 == 0 && y2 == 1) {
		sp_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(sp->getPosition());
		//firework->setEmitterMode(kCCParticleModeRadius);
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(sp);
	}

	if (x2 == 3 && y2 == 0 || x2 == 0 && y2 == 3) {
		if (page == 1) {
			auto Frame1 = SpriteFrame::create("animate/3.png", Rect(0, 0, 155, 160));
			auto Frame2 = SpriteFrame::create("animate/2.png", Rect(0, 0, 155, 160));
			Vector<SpriteFrame*> Frames(2);
			Frames.pushBack(Frame1);
			Frames.pushBack(Frame2);
			auto animation = Animation::createWithSpriteFrames(Frames, 0.4 / 2);
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, NULL);
			player2->runAction(seq);
		}
		if (page == 2) {
			auto Frame1 = SpriteFrame::create("animate/23.png", Rect(0, 0, 165, 160));
			auto Frame2 = SpriteFrame::create("animate/22.png", Rect(0, 0, 165, 160));
			Vector<SpriteFrame*> Frames(2);
			Frames.pushBack(Frame1);
			Frames.pushBack(Frame2);
			auto animation = Animation::createWithSpriteFrames(Frames, 0.4 / 2);
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, NULL);
			player2->runAction(seq);
		}

		sp_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(sp->getPosition());
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(sp);
		health2 -= 10;
		blood2->setPercentage(health2);
		blackart1 += 20;
		if (blackart1 > 100) {
			blackart1 = 100;
		}
		magic1->setPercentage(blackart1);
		if (health2 <= 0) {
			gameOver();
		}
	}

	if (x2 != 0 && y2 == 7 || x2 == 7 && y2 != 0) {
		tool1_ = false;
		this->removeChild(tool1);
	}

	if (x2 == 7 && y2 == 0 || x2 == 0 && y2 == 7) {
		tool1_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(sp->getPosition());
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(tool1);
		health1 += 50;
		if (health1 > 100)
			health1 = 100;
		blood1->setPercentage(health1);
		blackart1 += 50;
		if (blackart1 > 100)
			blackart1 = 100;
		magic1->setPercentage(blackart1);
	}


	if (x2 == -1 && y2 == 8 || x2 == 8 && y2 == -1) {
		st_ = false;
		this->removeChild(st);
	}
	if (x2 == 1 && y2 == 8 || x2 == 8 && y2 == 1) {
		st_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(st->getPosition());
		//firework->setEmitterMode(kCCParticleModeRadius);
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(st);
	}
	if (x2 == 0 && y2 == 8 || x2 == 8 && y2 == 0) {
		st_ = false;
		sp_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(st->getPosition());
		//firework->setEmitterMode(kCCParticleModeRadius);
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(st);
		this->removeChild(sp);
	}
	if (x2 == 8 && y2 == 2 || x2 == 2 && y2 == 8) {
		st_ = false;
		ParticleExplosion* firework = ParticleExplosion::create();
		firework->setPosition(st->getPosition());
		firework->setTotalParticles(600);
		addChild(firework);
		this->removeChild(st);
		health1 -= 20;
		blood1->setPercentage(health1);
		blackart2 += 20;
		if (blackart2 > 100)
			blackart2 = 100;
		magic2->setPercentage(blackart2);
		if (health1 <= 0) {
			gameOver();
		}
	}
	return true;
}

void HelloWorld::gameOver() {
	RenderTexture* sqr = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
	sqr->begin();
	// 访问当前运行屏幕 上的每个子结点
	Director::sharedDirector()->getRunningScene()->visit();
	// 结束绘制
	sqr->end();
	if (health1 > health2) {
		Director::getInstance()->pushScene(GameOver::createScene(sqr, true));
	}
	else {
		Director::getInstance()->pushScene(GameOver::createScene(sqr, false));
	}
}

//判断一次只有一个tool
void HelloWorld::tools() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float i = CCRANDOM_0_1();
	float j = CCRANDOM_0_1();
	if (i <= .05 && tool1_== false) {
		tool1 = Sprite::create("HelloWorld/tool1.png"); 
		//atool1->setScale(.6);
		tool1->setPosition(visibleSize.width * j, visibleSize.height * .8);
		tool1->setPhysicsBody(PhysicsBody::createBox(tool1->getContentSize(), PhysicsMaterial(1.0f, .0f, .0f)));
		tool1->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		tool1->setTag(7);
		addChild(tool1);
		tool1_ = true;
	}
}

void HelloWorld::simpleAI() {
	Animate* animate;
	if (page == 1) {
		auto Frame1 = SpriteFrame::create("animate/1.png", Rect(0, 0, 155, 160));
		auto Frame2 = SpriteFrame::create("animate/2.png", Rect(0, 0, 155, 160));
		Vector<SpriteFrame*> Frames(2);
		Frames.pushBack(Frame1);
		Frames.pushBack(Frame2);
		auto animation = Animation::createWithSpriteFrames(Frames, 0.3 / 2);
		animate = Animate::create(animation);
	}
	if (page == 2) {
		auto Frame1 = SpriteFrame::create("animate/21.png", Rect(0, 0, 165, 160));
		auto Frame2 = SpriteFrame::create("animate/22.png", Rect(0, 0, 165, 160));
		Vector<SpriteFrame*> Frames(2);
		Frames.pushBack(Frame1);
		Frames.pushBack(Frame2);
		auto animation = Animation::createWithSpriteFrames(Frames, 0.3 / 2);
		animate = Animate::create(animation);
	}

	auto moveleft = MoveTo::create(.3, Vec2(player2->getPositionX() - 50, player2->getPositionY()));
	auto moveright = MoveTo::create(.3, Vec2(player2->getPositionX() + 50, player2->getPositionY()));
	float i = CCRANDOM_0_1();
	if (i <= .25) {
		SimpleAudioEngine::getInstance()->playEffect("music/run.wav");
		auto seq = Spawn::createWithTwoActions(moveleft, animate);
		player2->runAction(seq);	
	}
	else if (i <= .5) {
		SimpleAudioEngine::getInstance()->playEffect("music/run.wav");
		auto seq = Spawn::createWithTwoActions(moveright, animate);
		player2->runAction(seq);
	}
	else if (i < .75) {
		if (blackart2 >= 80) {
			if (page == 1) {
				auto Frame1_ = SpriteFrame::create("animate/4.png", Rect(0, 0, 155, 160));
				auto Frame2_ = SpriteFrame::create("animate/2.png", Rect(0, 0, 155, 160));
				Vector<SpriteFrame*> Frames_(2);
				Frames_.pushBack(Frame1_);
				Frames_.pushBack(Frame2_);
				auto animation_ = Animation::createWithSpriteFrames(Frames_, 0.5 / 2);
				auto animate_ = Animate::create(animation_);
				auto seq_ = Sequence::create(animate_, NULL);
				player2->runAction(seq_);

				SimpleAudioEngine::getInstance()->playEffect("music/skill2.mp3");

				auto Frame1 = SpriteFrame::create("animate3/1.png", Rect(0, 0, 350, 500));
				auto Frame2 = SpriteFrame::create("animate3/2.png", Rect(0, 0, 350, 500));
				auto Frame3 = SpriteFrame::create("animate3/3.png", Rect(0, 0, 350, 500));
				auto Frame4 = SpriteFrame::create("animate3/4.png", Rect(0, 0, 350, 500));
				auto Frame5 = SpriteFrame::create("animate3/5.png", Rect(0, 0, 350, 500));
				auto Frame6 = SpriteFrame::create("animate3/6.png", Rect(0, 0, 350, 500));
				auto Frame7 = SpriteFrame::create("animate3/7.png", Rect(0, 0, 350, 500));
				auto s_sprite = Sprite::createWithSpriteFrame(Frame1);
				s_sprite->setPosition(player1->getPositionX() * 1.0, player1->getPositionY() * 1.0 + 20);
				addChild(s_sprite);
				Vector<SpriteFrame*> Frames(7);
				Frames.pushBack(Frame1);
				Frames.pushBack(Frame2);
				Frames.pushBack(Frame3);
				Frames.pushBack(Frame4);
				Frames.pushBack(Frame5);
				Frames.pushBack(Frame6);
				Frames.pushBack(Frame7);
				auto s_animation = Animation::createWithSpriteFrames(Frames, 0.1);
				auto s_animate = Animate::create(s_animation);
				auto seq = Sequence::create(s_animate, NULL);
				s_sprite->runAction(seq);
			}
			if (page == 2) {
				auto Frame1_ = SpriteFrame::create("animate/24.png", Rect(0, 0, 165, 160));
				auto Frame2_ = SpriteFrame::create("animate/22.png", Rect(0, 0, 165, 160));
				Vector<SpriteFrame*> Frames_(2);
				Frames_.pushBack(Frame1_);
				Frames_.pushBack(Frame2_);
				auto animation_ = Animation::createWithSpriteFrames(Frames_, 0.5 / 2);
				auto animate_ = Animate::create(animation_);
				auto seq_ = Sequence::create(animate_, NULL);
				player2->runAction(seq_);

				SimpleAudioEngine::getInstance()->playEffect("music/skill3.wav");

				auto Frame1 = SpriteFrame::create("animate5/1.png", Rect(0, 0, 350, 500));
				auto Frame2 = SpriteFrame::create("animate5/2.png", Rect(0, 0, 350, 500));
				auto Frame3 = SpriteFrame::create("animate5/3.png", Rect(0, 0, 350, 500));
				auto Frame4 = SpriteFrame::create("animate5/4.png", Rect(0, 0, 350, 500));
				auto Frame5 = SpriteFrame::create("animate5/5.png", Rect(0, 0, 350, 500));
				auto Frame6 = SpriteFrame::create("animate5/6.png", Rect(0, 0, 350, 500));
				auto Frame7 = SpriteFrame::create("animate5/7.png", Rect(0, 0, 350, 500));
				auto s_sprite = Sprite::createWithSpriteFrame(Frame1);
				s_sprite->setPosition(player1->getPositionX() * 1.3, player1->getPositionY() * 1.0 + 20);
				addChild(s_sprite);
				Vector<SpriteFrame*> Frames(7);
				Frames.pushBack(Frame1);
				Frames.pushBack(Frame2);
				Frames.pushBack(Frame3);
				Frames.pushBack(Frame4);
				Frames.pushBack(Frame5);
				Frames.pushBack(Frame6);
				Frames.pushBack(Frame7);
				auto s_animation = Animation::createWithSpriteFrames(Frames, 0.1);
				auto s_animate = Animate::create(s_animation);
				auto seq = Sequence::create(s_animate, NULL);
				s_sprite->runAction(seq);
			}

			blackart2 -= 80;
			magic2->setPercentage(blackart2);

			health1 -= 40;
			blood1->setPercentage(health1);
			if (health1 <= 0) {
				gameOver();
			}
		}
	}
	else if (st_ == false){
		if (page == 1) {
			auto Frame1 = SpriteFrame::create("animate/4.png", Rect(0, 0, 155, 160));
			auto Frame2 = SpriteFrame::create("animate/2.png", Rect(0, 0, 155, 160));
			Vector<SpriteFrame*> Frames(2);
			Frames.pushBack(Frame1);
			Frames.pushBack(Frame2);
			auto animation = Animation::createWithSpriteFrames(Frames, 0.5 / 2);
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, NULL);
			player2->runAction(seq);
		}
		if (page == 2) {
			auto Frame1 = SpriteFrame::create("animate/24.png", Rect(0, 0, 165, 160));
			auto Frame2 = SpriteFrame::create("animate/22.png", Rect(0, 0, 165, 160));
			Vector<SpriteFrame*> Frames(2);
			Frames.pushBack(Frame1);
			Frames.pushBack(Frame2);
			auto animation = Animation::createWithSpriteFrames(Frames, 0.5 / 2);
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, NULL);
			player2->runAction(seq);
		}
			st = Sprite::create("HelloWorld/weapon.png");
			st->setScale(.4);
			st->setPosition(player2->getPosition());
			auto body = PhysicsBody::createCircle(st->getContentSize().width / 2, PhysicsMaterial(3.0f, .0f, .0f));
			body->setVelocity(Vec2(-200, 300));
			st->setPhysicsBody(body);
			st->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			st->setTag(8);
			st_ = true;
			this->addChild(st);
			SimpleAudioEngine::getInstance()->playEffect("music/shoot.wav");
	}
	return;
}