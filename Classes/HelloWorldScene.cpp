#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand((unsigned int)time(NULL));
    Size visibleSize   = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
    GameBlock::removeAllBlocks();

    gameLayer = Node::create();
    
    addChild(gameLayer);
	 
    addNormalLine(3);
	addFlyShit();

	schedule(schedule_selector(HelloWorld::dropShit),3);

	//auto listener = EventListenerTouchAllAtOnce::create();
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan =[this]( Touch*   t, Event* event)
	{ 
		beginPoint = this->convertTouchToNodeSpace(t ); 
	 
		return true;
	};
	listener->onTouchMoved = [this]( Touch*   t, Event* event)
	{
	 
	
	};
	listener->onTouchEnded = [this]( Touch*   t, Event* event)
	{ 
		Point movePoint = this->convertTouchToNodeSpace(t );
		int xf = movePoint.x-beginPoint.x;
		int yf = movePoint.y-beginPoint.y;
		if(abs(xf) > 10 ){
			//char direction = (abs(xf) > abs(yf)) ? (xf < 15 ? 'a':'d'): (yf > 15 ? 'w' : 's');
			char direction =  xf < 0 ? 'l':'r';
			log("direction:%c",direction);
			flyShit->moveByDirection(direction);
		} 
	  
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,gameLayer);


	 auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(HelloWorld::onContactBegin, this);

    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void HelloWorld::dropShit(float dt){
    addNormalLine(3);
	auto bs = GameBlock::getBlocks();
	 
    for (auto it = bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void HelloWorld::addEdges(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*2),PHYSICSBODY_MATERIAL_DEFAULT,3);

	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(edgeShape);


}

 void HelloWorld::addFlyShit( ){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //GameBlock *flyShit;
    
     
	flyShit = GameBlock::createWithArgs( Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),"2",20,Color4B::BLACK);
    gameLayer->addChild(flyShit);
		 
	flyShit->setPhysicsBody(PhysicsBody::createBox(flyShit->getContentSize()));
	flyShit->getPhysicsBody()->setDynamic(false);

	flyShit->setPosition( visibleSize.width/4+visibleSize.width/8,flyShit->getContentSize().height/2+5);
    flyShit->setLineIndex(999);
     
     
}

 void HelloWorld::addNormalLine(int lineIndex){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    GameBlock *b;
    int blackIndex = rand()%4;
    int num = rand()%4;
	log("num:%d",num++);
	if(num>3){
		num=3;
	}
	int arr[3]={-1,-1,-1};
	 
    for (int i=0; i<num; i++) {
		b = GameBlock::createWithArgs(blackIndex==i?Color3B::BLUE:Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),"1024",20,Color4B::BLACK);
        gameLayer->addChild(b);
		b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
		b->getPhysicsBody()->setVelocity(Vec2(0,40));
		//b->setAnchorPoint(Point::ZERO);
		int tempIndex = i+blackIndex;
		if(tempIndex>=4){
			tempIndex=tempIndex-4;
		}

		b->setPosition(tempIndex*visibleSize.width/4+visibleSize.width/8, (lineIndex+(rand()%4*0.5f))*visibleSize.height/2);
        b->setLineIndex(lineIndex);
    }
    
    linesCount++;
}

bool HelloWorld::onContactBegin(   PhysicsContact& contact)
{
     
    return true;
}