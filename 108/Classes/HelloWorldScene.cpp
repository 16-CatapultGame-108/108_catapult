#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "EnemyLayer.h"

USING_NS_CC;

#define POWER_LIMIT 3.0
#define MIN_POWER 1.0
#define POWER_RATE 100
#define DIS_PLAYER 70

Scene* HelloWorld::createScene() {
    Scene* scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, -500));
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
    
    Sprite* background = Sprite::create("HelloWorld/bg.jpg");
    float oddsY = background->getContentSize().height / visibleSize.height;
    float odds = background->getContentSize().width / visibleSize.width;
    background->setScaleY(1 / oddsY);
    background->setScaleX(1 / odds);
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, 0);
    
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
    time->setColor(Color3B::RED);
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
    player1->setPhysicsBody(PhysicsBody::createBox(player1->getContentSize()));
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
    blood1->setPosition(visibleSize.width * .15, visibleSize.height * .9);
    auto ba = Sprite::create("HelloWorld/back.jpg");
    ba->setPosition(visibleSize.width * .15, visibleSize.height * .9);
    addChild(ba);
    addChild(blood1);
    
    auto progressSprite1_ = Sprite::create("HelloWorld/magic.jpg");
    magic1 = ProgressTimer::create(progressSprite1_);
    magic1->setType(ProgressTimer::Type::BAR);
    magic1->setMidpoint(ccp(0, 0.5));
    magic1->setBarChangeRate(ccp(1, 0));
    magic1->setPercentage(100);
    magic1->setPosition(visibleSize.width * .15, visibleSize.height * .85);
    auto ba2 = Sprite::create("HelloWorld/back.jpg");
    ba2->setPosition(visibleSize.width * .15, visibleSize.height * .85);
    addChild(ba2);
    addChild(magic1);
    
    //player2
    /*player2 = Sprite::create("HelloWorld/1.png");
    player2->setPosition(visibleSize.width * 7 / 8, 50 + player2->getContentSize().height / 2);
    player2->setPhysicsBody(PhysicsBody::createBox(player2->getContentSize()));
    health2 = 100;
    player2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    player2->setTag(3);
    this->addChild(player2);
     */
    
    auto progressSprite2 = Sprite::create("HelloWorld/blood.jpg");
    blood2 = ProgressTimer::create(progressSprite2);
    blood2->setType(ProgressTimer::Type::BAR);
    blood2->setMidpoint(ccp(0, 0.5));
    blood2->setBarChangeRate(ccp(1, 0));
    blood2->setPercentage(100);
    blood2->setPosition(visibleSize.width * .8, visibleSize.height * .8);
    addChild(blood2);
    
    EventListenerKeyboard* listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event){
        auto Frame1 = SpriteFrame::create("animate2/1.png", Rect(0, 0, 150, 172));
        auto Frame2 = SpriteFrame::create("animate2/2.png", Rect(0, 0, 150, 172));
        auto Frame3 = SpriteFrame::create("animate2/3.png", Rect(0, 0, 150, 172));
        Vector<SpriteFrame*> Frames(8);
        Frames.pushBack(Frame1);
        Frames.pushBack(Frame2);
        Frames.pushBack(Frame3);
        auto animation = Animation::createWithSpriteFrames(Frames, 0.2 / 3);
        auto animate = Animate::create(animation);
        
        if (code == EventKeyboard::KeyCode::KEY_A) {
            auto moveleft = MoveTo::create(.2,Vec2(player1->getPositionX() - 50, player1->getPositionY()));
            auto seq = Spawn::createWithTwoActions(moveleft, animate);
            player1->runAction(seq);
        }
        if (code == EventKeyboard::KeyCode::KEY_D) {
            auto moveright = MoveTo::create(.2,Vec2(player1->getPositionX() + 50, player1->getPositionY()));
            auto seq = Spawn::createWithTwoActions(moveright, animate);
            player1->runAction(seq);
        }
        if (code == EventKeyboard::KeyCode::KEY_W){
            if (player1->getPosition().y - 2 <= (50 + player1->getContentSize().height / 2)) {
                auto jump = MoveTo::create(.2, Vec2(player1->getPositionX(), player1->getPositionY() + 100));
                auto seq = Sequence::create(jump, NULL);
                player1->runAction(seq);
            }
        }
        if (code == EventKeyboard::KeyCode::KEY_SPACE) {
            HelloWorld::pause(this);
        }
        if (code == EventKeyboard::KeyCode::KEY_Q) {
            if (blackart1 >= 80) {
                blackart1 -= 80;
                magic1->setPercentage(blackart1);
                
                auto Frame1 = SpriteFrame::create("animate3/1.png", Rect(0, 0, 300, 500));
                auto Frame2 = SpriteFrame::create("animate3/2.png", Rect(0, 0, 300, 500));
                auto Frame3 = SpriteFrame::create("animate3/3.png", Rect(0, 0, 300, 500));
                auto Frame4 = SpriteFrame::create("animate3/4.png", Rect(0, 0, 300, 500));
                auto Frame5 = SpriteFrame::create("animate3/5.png", Rect(0, 0, 300, 500));
                auto Frame6 = SpriteFrame::create("animate3/6.png", Rect(0, 0, 300, 500));
                auto Frame7 = SpriteFrame::create("animate3/7.png", Rect(0, 0, 300, 500));
                auto s_sprite = Sprite::createWithSpriteFrame(Frame1);
                s_sprite->setPosition(player2->getPositionX() * 1.05, player2->getPositionY() * 1.1);
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
    
    //enemy
    enemys = EnemyLayer::createScene(player1);
    this->addChild(enemys, 2);
    
    //是否命中player
    EventListenerCustom* _listener = EventListenerCustom::create("hurtPlayer", [=](EventCustom* event){
        hurtPlayer(10);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
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
    auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2, PhysicsMaterial(3.0f, .001f, .0f));
    //double z = sin(dt);
    //log(z);
    body->setVelocity(Vec2(cos(dt)*power * POWER_RATE * 3, sin(dt)*power * POWER_RATE));
    //body->setGravityEnable(false);
    sp->setPhysicsBody(body);
    sp->setPositionX(x + cos(dt)*DIS_PLAYER);
    sp->setPositionY(y + sin(dt)*DIS_PLAYER);
    sp->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    sp->setTag(0);
    blackart1 += 20;
    if (blackart1 > 100) {
        blackart1 = 100;
    }
    magic1->setPercentage(blackart1);
    addChild(sp);
    sp_ = true;
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
        double diff_x = mouse_x - x, diff_y = visibleSize.height + mouse_y - y;
        double dt = atan2(diff_y, diff_x);
        timer->setRotation(-dt * 180 / 3.14);
		timer->setPositionX(x + cos(dt)*(DIS_PLAYER+5));
		timer->setPositionY(y + sin(dt)*(DIS_PLAYER+5));
		bar->setRotation(-dt * 180 / 3.14);
		bar->setPositionX(x + cos(dt)*DIS_PLAYER);
		bar->setPositionY(y + sin(dt)*DIS_PLAYER);
        //auto rotateTo = RotateTo::create(0.0f, 40.0f);
        //timer->runAction(rotateTo);
    }
}

void HelloWorld::updateTime(float temtime) {
    totalTime -= temtime;
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

//边界-1 石头0 地面1 人物1-2 人物2-3
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
    /*
     if (x2 == 2 && y2 == 0 || x2 == 0 && y2 == 2) {
     sp_ = false;
     ParticleGalaxy* firework = ParticleGalaxy::create();
     firework->setPosition(sp->getPosition());
     addChild(firework);
     this->removeChild(sp);
     health1 -= 10;
     blood1->setPercentage(health1);
     if (health1 <= 0) {
     gameOver();
     }
     }
     */
    
    if (x2 == 3 && y2 == 0 || x2 == 0 && y2 == 3) {
        sp_ = false;
        ParticleExplosion* firework = ParticleExplosion::create();
        firework->setPosition(sp->getPosition());
        firework->setTotalParticles(600);
        addChild(firework);
        this->removeChild(sp);
        health2 -= 10;
        blood2->setPercentage(health2);
        if (health2 <= 0) {
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

void HelloWorld::hurtPlayer(float p) {
    blood1->setPercentage(blood1->getPercentage()-p);
    if (blood1->getPercentage() <= 0)
        gameOver();
}
