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

	virtual void update(float dt); //֡ˢ��
	//virtual void onEnter();
	void testMouseEvent(); //������ʱ��
	void Launch(double power);//�����ڵ�

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

	//������Ӧ�й�
	bool flagA = true;//�����Ƿ�����ӦKey_A
	bool flagW = true;

	bool mousedown = false;            //�Ƿ���������
	bool readyLaunch = false;          //�Ƿ��ܹ�����
	int mouse_x, mouse_y;              //��ǰ�������
	ProgressTimer* pro1;
	bool full = false;
		//����������
};

