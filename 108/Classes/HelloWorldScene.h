#include "cocos2d.h"
#include "pause.h"
#include "GameOver.h"
#include "EnemyLayer.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	static HelloWorld* create(PhysicsWorld* world);
	virtual bool init(PhysicsWorld* world);

	void pause(Ref* ref);
	void gameOver();
	void updateTime(float temtime);

	//�ڵ�
	void prepare();
	void Launch(double power);
	virtual void update(float dt); //֡ˢ��

	bool onContactBegan(cocos2d::PhysicsContact& contact);

	cocos2d::Layer* enemys;

	//������
	ProgressTimer* timer;
	//��ʱ��
	float totalTime;
	cocos2d::Label* time;
	//ʯͷ
	Sprite* sp;
	bool sp_ = false;//һ��ֻ��Ͷһ��ʯͷ
	//player
	Sprite* player1;
	int health1;
	ProgressTimer * blood1;
	Sprite* player2;
	int health2;
	ProgressTimer * blood2;

	int mouse_x, mouse_y;//��ǰ�������
	
	bool mousedown = false;
	bool readyLaunch = false;
	bool full = false;
};
