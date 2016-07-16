#include "cocos2d.h"

USING_NS_CC;

class GameOver :public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene(RenderTexture* sqr, bool wol);
	virtual bool init();
	CREATE_FUNC(GameOver);
	void return2home(Ref *ref);
	void replay(Ref *ref);
};