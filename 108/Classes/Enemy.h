//
//  Enemy.h
//  demo
//
//  Created by apple on 16/7/7.
//
//

#ifndef Enemy_h
#define Enemy_h
#include "cocos2d.h"
#include "ArrowBezier.h"
#include "Arrow.h"
USING_NS_CC;

class Enemy : public Sprite {
public:
    static float offx,offy;
    Enemy();
    bool init(Vec2 loc);
    static Enemy* create(Vec2 loc, Sprite* target);
    
    void createEnemy(Vec2 loc);
    void createHpBar(Vec2 loc);
    void createBow(Vec2 loc);
    void shootArrow();
    //leave the clean-shoot zone
    //if already in, don't move
    void move();
    //remove enemy from scene
    void die();
    void moveFoward();
    void moveBackward();
    void behurt();
    void removeArrow();
    void rotateBow();
    //let enemy-layer hurt the target
    virtual void hurt();
    void calControlpoint();
    void update(float dt);
    //get the position of player and shootArrow
    void attack(float dt);
    bool died();
    
private:
    Sprite* bow;
    Sprite* enemyBody;
    Sprite* target;
    Arrow* arrow;
    bool aftershot;
    bool notified;
    Size winSize;
    Size eSize;
    Vec2 controlP;
    ccQuadBezierConfig bezier;
    ProgressTimer* hpBar;
    bool alive;
};

#endif /* Enemy_h */
