#include "cocos2d.h"

using namespace cocos2d;


class Myshow : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Myshow);

	Myshow(){};
	~Myshow() {};
    
    //show time
	void Schedule_();
	float getTime(){ return totalTime; }
	void updateTime(float dt);

	void playEffect(std::string s);

	void hurtplayer(float a);


private:
	float totalTime;
	Label* time;
	ProgressTimer * blood;
};

