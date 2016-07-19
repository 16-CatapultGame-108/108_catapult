//
//  Enemy.cpp
//  demo
//
//  Created by apple on 16/7/7.
//
//

#include "Enemy.h"
#include "math.h"
#define random(x) (rand()%x)
#include "Arrow.h"
float Enemy:: offx = -90;
float Enemy:: offy = 40;



Enemy::Enemy() {
    winSize = Director::getInstance()->getWinSize();
    bow = NULL;
    hpBar = NULL;
    enemyBody = NULL;
    alive = true;
    aftershot = false;
    notified = false;
    target = NULL;
    eSize = Size(0,0);
    bezier.controlPoint = Vec2(0, 0);
    bezier.endPosition = Vec2(0, 0);
}

Enemy* Enemy::create(Vec2 loc, Sprite* t) {
    Enemy* e = new Enemy();
    e->target = t;
    e->init(loc);
    //
    Size ss = e->enemyBody->getContentSize();
    Size st;
    st.width = ss.width/3;
    st.height = ss.height;
    PhysicsBody* b = PhysicsBody::createBox(st);
    b->setMass(1000);
    e->setPhysicsBody(b);
    e->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    //b->setDynamic(false);
    e->setTag(3);
    //
    e->autorelease();
    return e;
}

bool Enemy::init(Vec2 loc) {
    if (!Sprite::init()) {
        return false;
    }
    createEnemy(loc);
    createHpBar(loc);
    //createBow(loc);
    schedule(schedule_selector(Enemy::attack), 5.0f);
    scheduleUpdate();
    return true;
}

void Enemy::createEnemy(Vec2 loc) {
    enemyBody = Sprite::createWithSpriteFrameName("normal1.png");
    eSize = Size(enemyBody->getContentSize().width, enemyBody->getContentSize().height);
    //enemyBody->setAnchorPoint(Vec2(0.5f,0.5f));
    this->setPosition(Vec2(loc.x, loc.y+0.5f*eSize.height));
    this->addChild(enemyBody);
    
}

void Enemy::createHpBar(Vec2 loc) {
    hpBar = ProgressTimer::create(Sprite::create("Myshow/blood.jpg"));
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setMidpoint(Vec2(0, 0.5f));
    hpBar->setBarChangeRate(Vec2(1, 0));
    hpBar->setPercentage(100);
    hpBar->setPosition(Vec2(0, 0.5f*eSize.height+0.5f*hpBar->getContentSize().height));
    this->addChild(hpBar);
}

void Enemy::createBow(Vec2 loc) {
    bow = Sprite::createWithSpriteFrameName("playerarrow.png");
    bow->setPosition(Vec2(0.0f,0.0f));
    //bow->setAnchorPoint(Vec2(0.5f,0.5f));
    this->addChild(bow);
}

//leave the clean-shoot zone
//if already in, don't move
void Enemy::move() {
    Sprite* t = this->target;
    Vec2 targetpos = t->getParent()->convertToWorldSpace(t->getPosition());
    Vec2 mypos = this->getParent()->convertToWorldSpace(this->getPosition());
    float dist = fabsf(targetpos.x - mypos.x);
    if (winSize.width*0.2 < dist && dist < winSize.width*0.5) {
        int a = random(10);
        if (a > 5) {
            moveFoward();
        } else {
            moveBackward();
        }
        return;
    }
    if (mypos.x < winSize.width*0.1)
        moveBackward();
    else
        moveFoward();
}

void Enemy::moveBackward() {
    auto action = MoveBy::create(0.5f,Vec2(0.1*winSize.width,0));
    this->runAction(action);
}

void Enemy::moveFoward() {
    auto action = MoveBy::create(0.5f,Vec2(-0.1*winSize.width,0));
    this->runAction(action);
}

void Enemy::behurt() {
    this->hpBar->setPercentage(hpBar->getPercentage()-20.0f);
    if (hpBar->getPercentage() <= 0) {
        die();
    }
}

void Enemy::die() {
    this->alive = false;
}

void Enemy::rotateBow() {
    Vec2 cp = controlP;
    cp.y /= 2;
    auto rotateRadians = cp.getAngle();
    auto rotateDegrees = CC_RADIANS_TO_DEGREES(-rotateRadians);
    auto speed = 0.5 / M_PI;
    auto rotateDuration = fabs(rotateRadians * speed);
    bow->runAction( Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
                                     NULL));
}
//let enemy-layer hurt the target
//how to get `blood`?
//event dispacher?
void Enemy::hurt() {
    std::cout << "hurt\n";
}


//get the position of player and shootArrow
void Enemy::attack(float dt) {
    auto animation = AnimationCache::getInstance()->getAnimation("beforeAttack");
    auto animate = Animate::create(animation);
    auto animation2 = AnimationCache::getInstance()->getAnimation("afterAttack");
    auto animate2 = Animate::create(animation2);
    auto delayTime = DelayTime::create(0.5f);
    calControlpoint();
    //auto funcall0 = CallFunc::create(CC_CALLBACK_0(Enemy::rotateBow, this));
    auto funcall1= CallFunc::create(CC_CALLBACK_0(Enemy::shootArrow, this));
    auto funcall2= CallFunc::create(CC_CALLBACK_0(Enemy::move, this));
    enemyBody->runAction(Sequence::create(animate, funcall1, delayTime, animate2, funcall2,NULL));
}

void Enemy::shootArrow() {
    Vec2 cp = controlP;
    cp.y /= 2;
    auto rotateRadians = cp.getAngle();
    auto rotateDegrees = CC_RADIANS_TO_DEGREES(rotateRadians);
    Arrow* arrow = Arrow::createArrow(rotateDegrees, this->target);
    bezier.controlPoint = controlP;
    bezier.endPosition = Vec2(controlP.x*2,-(enemyBody->getContentSize().height)/2-offy);
    this->getParent()->addChild(arrow,5);
    Vec2 pos = this->getPosition();
    Vec2 apos = Vec2(pos.x+Enemy::offx,pos.y+Enemy::offy);
    arrow->setPosition(this->getParent()->convertToWorldSpace(apos));
    this->arrow = arrow;
    auto Action = ArrowBezier::create(1,bezier);
    auto delayTime = DelayTime::create(0.5f);
    auto clean = CallFunc::create(CC_CALLBACK_0(Enemy::removeArrow, this));
    aftershot = true;
    arrow->runAction(Sequence::create(Action,delayTime,clean,NULL));
}

void Enemy::removeArrow() {
    aftershot = false;
    notified = false;
    this->getParent()->cocos2d::Node::removeChild(this->arrow);
}

void Enemy::calControlpoint() {
    float dist = (target->getParent()->convertToWorldSpace(target->getPosition()).x
                  -this->getParent()->convertToWorldSpace(this->getPosition()).x)-offx;
    //float y = (winSize.width - dist)*winSize.height/winSize.width*2;
    float y = 400;
    float x = dist/2;
    controlP = Vec2(x,y);
}

void Enemy::update(float dt) {
    setRotation(0);
    if (aftershot && !notified) {
        if (arrow->getf()) {
            notified = true;
        //this->behurt();
        //射中player，分发事件
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("hurtPlayer");
        }
    }
}

bool Enemy::died() {
    return !alive;
}

