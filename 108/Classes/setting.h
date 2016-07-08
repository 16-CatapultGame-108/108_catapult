#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Setting : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Setting);

	void return2home(Ref *ref);
	void sliderChange(Ref* psender, Control::EventType event);
	void sliderChange2(Ref* psender, Control::EventType event);
};
