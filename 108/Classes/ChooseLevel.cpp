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

	auto background = Sprite::create("ChooseLevel/background.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	float oddsY = background->getContentSize().height / visibleSize.height;
	float odds = background->getContentSize().width / visibleSize.width;
	background->setScaleY(1 / oddsY);
	background->setScaleX(1 / odds);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	auto change = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(ChooseLevel::return2home, this));
	auto menutoggle = Menu::create(change, NULL);
	menutoggle->setPosition(Director::getInstance()->getVisibleSize().width * 0.85, Director::getInstance()->getVisibleSize().height * 0.8);
	this->addChild(menutoggle, 1);

	scrollview = ScrollView::create(Size(winSize.width, winSize.height));
	Layer* layer = Layer::create();
	for (int i = 0; i < 3; i++)
	{
		String * string = String::createWithFormat("ChooseLevel/%d.jpg", i);
		Sprite * sprite = Sprite::create(string->getCString());
		sprite->setScale(.4);
		//将所有的精灵都放到屏幕的中间显示
		sprite->setPosition(ccpAdd(ccp(winSize.width / 2, winSize.height / 2),
			ccp(winSize.width*i, 0)));
		layer->addChild(sprite);
	}
	scrollview->setContainer(layer);
	//setContentSize()设置内容区的大小
	scrollview->setContentSize(Size(winSize.width * 3, winSize.height));

	scrollview->setTouchEnabled(false);
	//设置里边内容的偏移量  
	//scrollview->setContentOffset(Point(0, 0));
	this->addChild(scrollview);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ChooseLevel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChooseLevel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChooseLevel::onTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool ChooseLevel::onTouchBegan(Touch* touch, Event* event)
{    
	this->m_touchPoint = touch->getLocation();
	this->m_offsetPoint = this->scrollview->getContentOffset();
	return true;
}

void ChooseLevel::onTouchMoved(Touch* touch, Event* event) {
	Point point = touch->getLocation();
	Point direction = point - this->m_touchPoint;
	//Point spriteDirection = ccpAdd(this->m_offsetPoint,direction);  
	//只在x方向偏移 
	Point spriteDirection = Point(direction.x + this->m_offsetPoint.x, 0);
	this->scrollview->setContentOffset(spriteDirection);
}

void ChooseLevel::onTouchEnded(Touch* touch, Event* event) {
	Point endPoint = touch->getLocation();
	float distance = endPoint.x - this->m_touchPoint.x;
	//手指移动的距离小于20的时候，就将偏移量作为0处理  
	if (fabs(distance) < 20)
	{
		CCPoint touchPoint = touch->getLocation(); // Get the touch position
		touchPoint = this->convertToWorldSpace(touchPoint);
		float x = touchPoint.x - myoffset;
		float y = touchPoint.y;
		CCLOG("the x ");
		CCLOG("%f", x);
		CCLOG("the y ");
		CCLOG("%f", y);

		Size winSize = Director::getInstance()->getWinSize();
		if (x >= winSize.width / 2 - 200 && x <= winSize.width / 2 + 200 && y >= winSize.height / 2 - 110 && y <= winSize.height / 2 + 110)
		{
			if (m_nCurPage == 0 || m_nCurPage == 1)
				Director::getInstance()->pushScene(TransitionShrinkGrow::create(.5, HelloWorld::createScene(m_nCurPage + 1))); //choose scene1
		}
	}
	else
	{
		//将偏移量作为参数传进来  
		this->adjustScrollView(distance);
	}
}

void ChooseLevel::adjustScrollView(float offset)
{
	Size winSize = Director::getInstance()->getWinSize();
	// 我们根据 offset 的实际情况来判断移动效果  
	//如果手指往左划，offset大于0，说明页面在减小，往右增大  
	if (offset < 0)
		m_nCurPage++;
	else if (offset > 0)
		m_nCurPage--;

	//不允许超出最左边的一页和最右边的一页  
	if (m_nCurPage < 0)
		m_nCurPage = 0;
	else if (m_nCurPage > 2)
		m_nCurPage = 2;

	Point adjustPoint = Point(-winSize.width * m_nCurPage, 0);
	//这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量  
	this->scrollview->setContentOffsetInDuration(adjustPoint, 0.3f);
}

void ChooseLevel::return2home(Ref* ref) {
	Director::getInstance()->popScene();
}