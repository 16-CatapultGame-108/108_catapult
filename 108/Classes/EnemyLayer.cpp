//
//  EnemyLayer.cpp
//  demo
//
//  Created by apple on 16/7/7.
//
//

#include "EnemyLayer.h"

Sprite* EnemyLayer::player = NULL;

EnemyLayer::EnemyLayer () {
    this->enemyn = 1;
    this->winSize = Director::getInstance()->getWinSize();
    enemys.clear();
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/texture.plist", "Enemy/texture.pvr.ccz");
    
    auto animation = createAnimation("player", 8, 0.06f);
    AnimationCache::getInstance()->addAnimation(animation, "player");
    for (int i = 0; i < enemyn; i++) {
        enemys.pushBack(Enemy::create(Vec2(winSize.width*5/6,50), EnemyLayer::player));
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

void EnemyLayer::update(float dt) {
    for (auto sp:enemys) {
        if (sp->died()) {
            this->removeChild(sp);
        }
    }
}

