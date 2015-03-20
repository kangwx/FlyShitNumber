#include "GameScene.h"

USING_NS_CC; 

#define DROP_SHIT_MASK 001
#define FLY_SHIT_MASK 010

int GameScene::m_bestScore = 0;
int GameScene::m_scoreNum = 2048;
int	GameScene::m_reliveCount=10;
int GameScene::gameCount=0;

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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-550));
    
    
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
	int zorder = 1000;

    srand((unsigned int)time(NULL));
    visibleSize   = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	flyNumber =GameScene::m_scoreNum;
	//GameScene::m_scoreNum = 2;
	shitCount = 0;

	auto bg = Sprite::create("bg.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);

	auto btn_menu = MenuItemImage::create(
		"pause.png",
		"pause.png",
		CC_CALLBACK_1(GameScene::menuPauseCallback, this));
	btn_menu->setPosition(Point(visibleSize.width/2 + 300  , visibleSize.height/2 + 400 ));

	auto btn_music = MenuItemImage::create(
		"music_on.png",
		"music_on.png",
		CC_CALLBACK_1(GameScene::menuMusicCallback, this));
	btn_music->setPosition(Point(visibleSize.width/2 - 350  , visibleSize.height/2 + 400 ));

	
	auto menu = Menu::create(btn_menu,btn_music ,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, zorder++); 
	startGame();

	
    return true;
}
void GameScene::menuPauseCallback(cocos2d::Ref* pSender){
	auto director = Director::getInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);  
	renderTexture->begin();  
	this->getParent()->visit();  
	renderTexture->end();

	//m_bestScore =  PauseScene::m_scoreNum; 
	director->pushScene(PauseScene::scene(renderTexture,true));
	//director->pushScene(OverScene::scene(renderTexture,true));
}
void GameScene::menuMusicCallback(cocos2d::Ref* pSender){
	 
}
void GameScene::startGame(){
	txt_score = Label::create();
	txt_score->setPosition(Point(visibleSize.width/2 -250 , visibleSize.height/2+500 ));
	txt_score->setString("Score:");
    txt_score->setSystemFontSize(40);
	txt_score->setTextColor(Color4B::BLUE);
	this->addChild(txt_score,1001);

	score = Label::create();
	score->setPosition(Point(visibleSize.width/2 -130 , visibleSize.height/2+500 ));
	score->setString(num2str( GameScene::m_scoreNum));
    score->setSystemFontSize(40);
	score->setTextColor(Color4B::BLUE);
	this->addChild(score,1001);

	txt_best_score = Label::create();
	txt_best_score->setPosition(Point(visibleSize.width/2 -250 , visibleSize.height/2+400 ));
	txt_best_score->setString("Best: ");
    txt_best_score->setSystemFontSize(40);
	txt_best_score->setTextColor(Color4B::BLACK);
	this->addChild(txt_best_score,1001);

	GameScene::m_reliveCount = Cocos2DxFileUtils::getIntegerDataFromSD(SD_RELIVECOUNT,10); 
	int best = Cocos2DxFileUtils::getIntegerDataFromSD(SD_BESTSCORE,0); 
	m_bestScore=best;
	bestScore = Label::create();
	bestScore->setPosition(Point(visibleSize.width/2 -130 , visibleSize.height/2+400 ));
	bestScore->setString(num2str(m_bestScore));
    bestScore->setSystemFontSize(40);
	bestScore->setTextColor(Color4B::BLACK);
	this->addChild(bestScore,1001);

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


	flyShit = GameBlock::createWithArgs( Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),label,40,Color4B::BLACK,true);
    gameLayer->addChild(flyShit);
	flyShit->setTag(flyNumber);
	flyShit->setPhysicsBody(PhysicsBody::createCircle(flyShit->getContentSize().width/4));
	flyShit->getPhysicsBody()->setDynamic(false);
	 
	flyShit->getPhysicsBody()->setContactTestBitmask(FLY_SHIT_MASK);

	flyShit->setPosition( visibleSize.width/4+visibleSize.width/8,flyShit->getContentSize().height/2+5);
    flyShit->setLineIndex(9999);
	
     
}
 
void GameScene::addDropShit(float dt){
	if(shitCount>0){
		int lineIndex =3;
		int blackIndex = rand()%4;  
		//int shitNumber =rand()%3*flyNumber+flyNumber; 
		int randNum = rand()%3;
		int shitNumber=flyNumber;
		while(randNum>0){
			shitNumber*=2;
			randNum--;
		}
		 
		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameBlock *b;
		b = GameBlock::createWithArgs( Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),num2str(shitNumber),40,Color4B::BLACK,false);
        gameLayer->addChild(b);
		b->setPhysicsBody(PhysicsBody::createCircle(b->getContentSize().width/4));
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
			char newTexture[100];
			int newTag = tagA+tagA;
			sprintf(newTexture,"shit_%d.png",newTag);
			if(contact.getShapeA()->getBody()->getContactTestBitmask() == FLY_SHIT_MASK){ 
				Label* l =(Label*) spriteA->getChildByName("num");
				Sprite* img =(Sprite*) spriteA->getChildByName("img");
				img->setTexture(newTexture);
				 
				log("new tag: %d",newTag);
				l->setString( num2str(tagA+tagA) ); 
				spriteA->setTag(newTag);
				spriteA->runAction(
					Sequence::create(
					ScaleTo::create(0.3f,1.5f),
					ScaleTo::create(0.3f,1),
					NULL
					)
					);
				  
				spriteB->removeFromParent(); 
				
			}

			if(contact.getShapeB()->getBody()->getContactTestBitmask() == FLY_SHIT_MASK){
				Label* l =(Label*) spriteB->getChildByName("num");
				 Sprite* img =(Sprite*) spriteB->getChildByName("img");
				 img->setTexture(newTexture); 
				log("new tag: %d",newTag);
				l->setString( num2str(tagA+tagA) ); 
				spriteB->setTag(newTag);
				spriteB->runAction(
					Sequence::create(
					ScaleTo::create(0.3f,1.5f),
					ScaleTo::create(0.3f,1),
					NULL
					)
					);
				 
				spriteA->removeFromParent();
			}
			 GameScene::m_scoreNum = newTag;
			score->setString(num2str( GameScene::m_scoreNum));
			flyNumber = newTag;
		} else{
			log("taga != tagb");
			auto director = Director::getInstance();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);  
			renderTexture->begin();  
			this->getParent()->visit();  
			renderTexture->end();

			m_bestScore =  GameScene::m_scoreNum; 
			director->pushScene(OverScene::scene(renderTexture,true));
			 
		}
		 break;
	 case DROP_SHIT_MASK:
		 log("onContactBegin DROP_SHIT_MASK");
		 break;
	 }
	

    return true;
}