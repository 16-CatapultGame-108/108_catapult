#include "cocos2d.h"

class helpScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(helpScene);
	void return2home(Ref *ref);
};