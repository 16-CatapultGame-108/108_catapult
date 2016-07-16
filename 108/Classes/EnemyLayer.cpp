//
//  EnemyLayer.cpp
//  demo
//
//  Created by apple on 16/7/7.
//
//

#include "EnemyLayer.h"
#include<time.h>

Sprite* EnemyLayer::player = NULL;

EnemyLayer::EnemyLayer () {
    srand((int)time(0));
    this->enemyn = 1;
    this->winSize = Director::getInstance()->getWinSize();
    enemys.clear();
    died.clear();
    init();
}

Layer* EnemyLayer::createScene(cocos2d::Sprite *target) {
    EnemyLayer::player = target;
    auto layer = new EnemyLayer();
    layer->autorelease();
    return layer;
}

bool EnemyLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/enemy.plist", "Enemy/enemy.png");
    
    auto animation = createAnimation("hit1_", 12, 0.06f);
    AnimationCache::getInstance()->addAnimation(animation, "beforeAttack");
    auto animation2 = createAnimation("hit2_", 7, 0.06f);
    AnimationCache::getInstance()->addAnimation(animation2, "afterAttack");
    for (int i = 0; i < 1; i++) {
        enemys.pushBack(Enemy::create(Vec2(winSize.width*5/6,0), EnemyLayer::player));
    }
    for (auto sp:enemys) {
        this->addChild(sp);
    }
    scheduleUpdate();
    return true;
}

Animation* EnemyLayer::createAnimation(std::string prefixName, int framesNum, float delay) {
    Vector<SpriteFrame*> animFrames;
    
    for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "%i.png",  i);
        std::string str =  prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}

void EnemyLayer::removeDied() {
    for (auto sp:died) {
        enemys.eraseObject(sp);
        this->removeChild(sp);
    }
    died.clear();
}

void EnemyLayer::update(float dt) {
    for (auto sp:enemys) {
        if (sp->died()) {
            auto delayTime = DelayTime::create(1.0f);
            auto clean = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeDied, this));
            died.pushBack(sp);
            this->runAction(Sequence::create(delayTime,clean,NULL));
        }
    }
}

