//
//  Arrow.cpp
//  demo
//
//  Created by apple on 16/7/8.
//
//

#include "Arrow.h"
#include "math.h"


Arrow::Arrow(){}

Arrow* Arrow::createArrow(float f, Sprite* t) {
    Arrow* ar = new Arrow();
    ar->arrowBody = Sprite::create("HelloWorld/stone.png");
    ar->setPosition(Vec2(0,0));
    //ar->setRotation(-f);
    ar->addChild(ar->arrowBody);
    ar->f = false;
    ar->t = t;
    ar->autorelease();
    ar->init();
    return ar;
}

bool Arrow::init() {
    if (!Sprite::init())
        return false;
    scheduleUpdate();
    return true;
}

void Arrow::testAndSetf() {
    if (this->f == true)
        return;
    Vec2 p = this->getParent()->convertToWorldSpace(this->getPosition());
    Vec2 tl = t->getParent()->convertToWorldSpace(t->getPosition());
    Vec2 dt = p-tl;
    Size goalSize = t->getContentSize();
    float dtx, dty;
    dtx = fabsf(dt.x);
    dty = fabsf(dt.y);
    if (dtx < goalSize.width && dty < goalSize.height) {
        this->f = true;
    }
}

void Arrow::update(float dt) {
    testAndSetf();
}

bool Arrow::getf() {
    return f;
}
