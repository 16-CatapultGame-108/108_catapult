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
	bool onTouchBegan(Touch* touch, Event* event);//������ʼ����

	void onTouchMoved(Touch* touch, Event* event);//�����ƶ�����

	void onTouchEnded(Touch* touch, Event* event);//������������

private:
	ScrollView* scrollview;
	EventDispatcher* dispatcher;
	float myoffset = 0;
};

