#include "cocos2d.h"

USING_NS_CC;

class pause:public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene(RenderTexture* sqr);
	virtual bool init();
	CREATE_FUNC(pause);
	void return2home(Ref *ref);
	void replay(Ref *ref);
	void resume(Ref *ref);
};