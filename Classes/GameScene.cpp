#include "GameScene.h"

USING_NS_CC; 

#define DROP_SHIT_MASK 001
#define FLY_SHIT_MASK 010


string GameScene::num2str(double i)
{

	stringstream ss;

	ss << i;

	return ss.str();
}
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-500));
    
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
	
	flyNumber = 2;
	scoreNum = 2;
	shitCount = 0;

	auto bg = Sprite::create("bg.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
	
	score = Label::create();
	score->setPosition(Point(visibleSize.width/2 -350 , visibleSize.height/2+500 ));
	score->setString(num2str(scoreNum));
    score->setSystemFontSize(40);
	score->setTextColor(Color4B::BLUE);
	this->addChild(score,1001);

    GameBlock::removeAllBlocks();

    gameLayer = Node::create();
    
    addChild(gameLayer);
	 
    addNormalLine(3);
	addFlyShit();

	schedule(schedule_selector(GameScene::dropShit),3);
	schedule(schedule_selector(GameScene::addDropShit),0.5f);

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
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);

    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void GameScene::dropShit(float dt){
    addNormalLine(3);
	auto bs = GameBlock::getBlocks();
	 
    for (auto it = bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void GameScene::addEdges(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*2),PHYSICSBODY_MATERIAL_DEFAULT,3);

	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(edgeShape);
	 
}

 void GameScene::addFlyShit( ){
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    //GameBlock *flyShit;
    
	//char[ ] cNumber="2"; 
	//int shitNumber = flyNumber;
	//sprintf(cNumber, "%d",flyNumber); 
	string label = num2str(flyNumber);

	flyShit = GameBlock::createWithArgs( Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),label,40,Color4B::BLACK);
    gameLayer->addChild(flyShit);
	flyShit->setTag(flyNumber);
	flyShit->setPhysicsBody(PhysicsBody::createBox(flyShit->getContentSize()));
	flyShit->getPhysicsBody()->setDynamic(false);
	 
	flyShit->getPhysicsBody()->setContactTestBitmask(FLY_SHIT_MASK);

	flyShit->setPosition( visibleSize.width/4+visibleSize.width/8,flyShit->getContentSize().height/2+5);
    flyShit->setLineIndex(9999);
	
     
}
 
void GameScene::addDropShit(float dt){
	if(shitCount>0){
		int lineIndex =3;
		int blackIndex = rand()%4;
		int shitNumber =rand()%3*flyNumber+flyNumber; 
		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameBlock *b;
		b = GameBlock::createWithArgs( Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),num2str(shitNumber),40,Color4B::BLACK);
        gameLayer->addChild(b);
		b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
		//b->getPhysicsBody()->setVelocity(Vec2(0,40));
		b->getPhysicsBody()->setContactTestBitmask(DROP_SHIT_MASK);
		b->setTag(shitNumber);
		//b->setAnchorPoint(Point::ZERO);
		int tempIndex =  blackIndex;
		if(tempIndex>=4){
			tempIndex=tempIndex-4;
		}

		b->setPosition(tempIndex*visibleSize.width/4+visibleSize.width/8,  lineIndex *visibleSize.height/2);
        b->setLineIndex(lineIndex); 
		shitCount--;
		log("shitNumber:%d",shitCount);
	}
}
 void GameScene::addNormalLine(int lineIndex){
    
    
    int num = rand()%4;
	log("num:%d",num++);
	if(num>3){
		num=3;
	} 
    
    shitCount=num;
     
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{

     
auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	 int tagA = spriteA->getTag();
	 int tagB = spriteB->getTag();
	 switch(contact.getShapeA()->getBody()->getContactTestBitmask() |
		 contact.getShapeB()->getBody()->getContactTestBitmask()){
	 case FLY_SHIT_MASK | DROP_SHIT_MASK:
		log("onContactBegin FLY_SHIT_MASK and DROP_SHIT_MASK tagA:%d",tagA);
		if(tagA==tagB){
			int newTag = tagA+tagA;
			if(contact.getShapeA()->getBody()->getContactTestBitmask() == FLY_SHIT_MASK){ 
				Label* l =(Label*) spriteA->getChildByName("num");
				
				log("new tag: %d",newTag);
				l->setString( num2str(tagA+tagA) ); 
				spriteA->setTag(newTag);

				spriteB->removeFromParent(); 
				
			}

			if(contact.getShapeB()->getBody()->getContactTestBitmask() == FLY_SHIT_MASK){
				Label* l =(Label*) spriteB->getChildByName("num");
				 
				log("new tag: %d",newTag);
				l->setString( num2str(tagA+tagA) ); 
				spriteB->setTag(newTag);

				spriteA->removeFromParent();
			}
			scoreNum = newTag;
			score->setString(num2str(scoreNum));
			flyNumber = newTag;
		} else{
			log("taga != tagb");
			auto director = Director::getInstance();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);  
			renderTexture->begin();  
			this->getParent()->visit();  
			renderTexture->end();

			
			director->pushScene(OverScene::scene(renderTexture,true));
			 
		}
		 break;
	 case DROP_SHIT_MASK:
		 log("onContactBegin DROP_SHIT_MASK");
		 break;
	 }
	

    return true;
}