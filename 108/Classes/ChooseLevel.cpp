#include "ChooseLevel.h"
#include "HelloWorldScene.h"
using namespace std;

Scene* ChooseLevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ChooseLevel::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool ChooseLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scrollview = ScrollView::create(Size(winSize.width, winSize.height));

	scrollview->setDirection(ScrollView::Direction::HORIZONTAL);
	Layer* layer = Layer::create();
	for (int i = 0; i < 3; i++)
	{
		String * string = String::createWithFormat("%d.jpg", i);
		Sprite * sprite = Sprite::create(string->getCString());
		sprite->setScale(2.0, 2.0);
		//将所有的精灵都放到屏幕的中间显示
		sprite->setPosition(ccpAdd(ccp(winSize.width / 2, winSize.height / 2),
			ccp(winSize.width*i, 0)));
		layer->addChild(sprite);
	}
	scrollview->setContainer(layer);
	//setContentSize()设置内容区的大小
	scrollview->setContentSize(Size(winSize.width * 3, winSize.height));
	addChild(scrollview, 1);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ChooseLevel::onTouchBegan, this);

	listener->onTouchMoved = CC_CALLBACK_2(ChooseLevel::onTouchMoved, this);

	listener->onTouchEnded = CC_CALLBACK_2(ChooseLevel::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

/*void ChooseLevel::scrollViewDidScroll(ScrollView* view) {
	int a = 0;
}

void ChooseLevel::scrollViewDidZoom(ScrollView* view) {
	int b = 0;
}
*/

bool ChooseLevel::onTouchBegan(Touch* touch, Event* event)
{    
	//Point touchPoint = convertTouchToNodeSpace(touch);
	CCPoint touchPoint = touch->getLocation(); // Get the touch position
	touchPoint = this->convertToWorldSpace(touchPoint);
	float x = touchPoint.x - myoffset;
	float y = touchPoint.y;
	CCLOG("the x ");
	CCLOG("%f", x);
	CCLOG("the y ");
	CCLOG("%f", y);

	Size winSize = Director::getInstance()->getWinSize();
	if (x >= winSize.width / 2 - 220 && x <= winSize.width / 2 + 220 && y >= winSize.height / 2 - 124 && y <= winSize.height / 2 + 124)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene()); //choose scene1
	}
	if (x >= 1.5* winSize.width - 220 && x <= 1.5 * winSize.width + 220 && y >= winSize.height / 2 - 124 && y <= winSize.height / 2 + 124)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());   //choose scene2
	}
	return true;
}

void ChooseLevel::onTouchMoved(Touch* touch, Event* event)
{
	int a = 5;
}

void ChooseLevel::onTouchEnded(Touch* touch, Event* event) {
	scrollview->unscheduleAllSelectors();
	float x = scrollview->getContentOffset().x;
	float offset = -x / Director::getInstance()->getWinSize().width;
	int temp = offset;
	if (offset - temp > 0.5) temp++;
	myoffset = -temp * Director::getInstance()->getWinSize().width;
	scrollview->setContentOffsetInDuration(Vec2(-temp * Director::getInstance()->getWinSize().width, 0), 0.3f);
}