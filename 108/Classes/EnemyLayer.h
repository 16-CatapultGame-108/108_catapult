//
//  EnemyLayer.h
//  demo
//
//  Created by apple on 16/7/7.
//
//

#ifndef EnemyLayer_h
#define EnemyLayer_h

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class EnemyLayer : public Layer {
public:
    EnemyLayer();
    static cocos2d::Layer* createScene(Sprite* target);
    virtual bool init();
   
	
	void removeDied();
    void update(float dt);
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    
private:
    static Sprite* player;
    Vector<Enemy*> enemys;
    Vector<Enemy*> died;
    Size winSize;
    int enemyn;
};
#endif /* EnemyLayer_h */
