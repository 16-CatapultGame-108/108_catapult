//
//  Arrow.h
//  demo
//
//  Created by apple on 16/7/8.
//
//

#ifndef Arrow_h
#define Arrow_h
#include "cocos2d.h"

USING_NS_CC;

class Arrow : public Sprite {
public:
    Arrow();
    static Arrow* createArrow(float r, Sprite* t);
    virtual bool init();
    void testAndSetf();
    void update(float dt);
    bool getf();
private:
    //the arrow hit goal
    bool f;
    Sprite* arrowBody;
    Sprite* t;
};

#endif /* Arrow_h */
