#pragma once
#include <string>
#include "Myshow.h"
#include "EnemyLayer.h"
#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:
	static Scene* createScene();
	static HelloWorld* create(PhysicsWorld* world);
	bool init(PhysicsWorld* world);

	virtual void update(float dt); //帧刷新
	//virtual void onEnter();
	void testMouseEvent(); //鼠标控制时间
	void Launch(double power);//发射炮弹

	void testKeyboardEvent();
	void pressA();
	void pressW();
	void pressspace();
	void pause(Ref *ref);
	/*void testContact();
	bool onContactBegan(PhysicsContact& contact);
	void testContactFilter();*/


private:
	HelloWorld();
	~HelloWorld();

	PhysicsWorld* m_world;
	EventDispatcher* dispatcher;
	Sprite *player;
	cocos2d::Layer* enemys;
	Myshow* myshow;

	//键盘响应有关
	bool flagA = true;//代表是否能响应Key_A
	bool flagW = true;

	bool mousedown = false;            //是否按下鼠标左键
	bool readyLaunch = false;          //是否能够发射
	int mouse_x, mouse_y;              //当前鼠标坐标
	ProgressTimer* pro1;
	bool full = false;
		//蓄力进度条
};

