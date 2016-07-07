#pragma once
#include <string>
#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:
	static Scene* createScene();
	static HelloWorld* create(PhysicsWorld* world);
	bool init(PhysicsWorld* world);



	void testKeyboardEvent();
	void pressA();
	void pressW();
	void pressspace();

	/*void testContact();
	bool onContactBegan(PhysicsContact& contact);
	void testContactFilter();*/


private:
	HelloWorld();
	~HelloWorld();

	PhysicsWorld* m_world;
	EventDispatcher* dispatcher;
	Sprite *player;

	//������Ӧ�й�
	bool flagA = true;//�����Ƿ�����ӦKey_A
	bool flagW = true;

};

