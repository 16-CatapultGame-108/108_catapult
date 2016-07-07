#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class ChooseLevel :public Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseLevel);
	/*
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);*/
	bool onTouchBegan(Touch* touch, Event* event);//触摸开始方法

	void onTouchMoved(Touch* touch, Event* event);//触摸移动方法

	void onTouchEnded(Touch* touch, Event* event);//触摸结束方法
	void adjustScrollView(float offset);
private:
	ScrollView* scrollview;
	
	float myoffset = 0;

	Point m_touchPoint;

	Point m_offsetPoint;
	int m_nCurPage;
};

