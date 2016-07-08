#ifndef __MainPage_SCENE_H__
#define __MainPage_SCENE_H__

#include "cocos2d.h"

class MainPage : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    CREATE_FUNC(MainPage);
	void helpscene(Ref *ref);
	void startscene(Ref *ref);
	void closegame(Ref *ref);
	void setting(Ref *ref);
};

#endif // __MainPage_SCENE_H__
