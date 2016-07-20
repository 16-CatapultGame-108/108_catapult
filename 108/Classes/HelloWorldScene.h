#include "cocos2d.h"
#include "pause.h"
#include "GameOver.h"
#include "EnemyLayer.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene(int t);
	static HelloWorld* create(PhysicsWorld* world);
	virtual bool init(PhysicsWorld* world);

	void pause(Ref* ref);
	void gameOver();
	void updateTime(float temtime);

	//炮弹
	void prepare();
	void Launch(double power);
	virtual void update(float dt); //帧刷新

	void hurtPlayer(float);

	bool onContactBegan(cocos2d::PhysicsContact& contact);


	//随机出现的道具
	void tools();
	Sprite* tool1;
	int tool1_ = false;

	cocos2d::Layer* enemys;

	//力度条
	ProgressTimer* timer;
	Sprite* bar;
	//计时器
	float totalTime;
	cocos2d::Label* time;
	//石头
	Sprite* sp;
	bool sp_ = false;//一次只能投一个石头
	//player
	Sprite* player1;
	int health1;
	int blackart1;
	ProgressTimer * blood1;
	ProgressTimer * magic1;
	Sprite* player2;
	int health2 = 100;
	ProgressTimer * blood2;

	int mouse_x, mouse_y;//当前鼠标坐标
	
	bool mousedown = false;
	bool readyLaunch = false;
	bool full = false;
	//player 减血
        void hurtPlayer(float p);
};
