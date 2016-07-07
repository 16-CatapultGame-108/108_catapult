#include "cocos2d.h"

using namespace cocos2d;


class Myshow : public cocos2d::Layer
{
public:
	static Myshow* getInstance();

    virtual bool init();
    
    //show time
	void Schedule_();
	float getTime(){ return totalTime; }
	void updateTime(float dt);

	void preloadMusic();
	void playBgm();
	void playEffect(std::string s);

	void hurtplayer(float a);


private:
	static Myshow* myshow ;
	Myshow(){};
	~Myshow() {};
	float totalTime;
	Label* time;
	ProgressTimer * blood;
};

