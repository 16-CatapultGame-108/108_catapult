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

	//炮弹
	void prepare();
	void Launch(double power);
	virtual void update(float dt); //帧刷新

	bool onContactBegan(cocos2d::PhysicsContact& contact);

	cocos2d::Layer* enemys;

	//力度条
	ProgressTimer* timer;
	//计时器
	float totalTime;
	cocos2d::Label* time;
	//石头
	Sprite* sp;
	bool sp_ = false;//一次只能投一个石头
	//player
	Sprite* player1;
	int health1;
	ProgressTimer * blood1;
	Sprite* player2;
	int health2;
	ProgressTimer * blood2;

	int mouse_x, mouse_y;//当前鼠标坐标
	
	bool mousedown = false;
	bool readyLaunch = false;
	bool full = false;
};
