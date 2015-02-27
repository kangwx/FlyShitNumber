#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    
     Size visibleSize   = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
    gameLayer = Node::create();
    
    addChild(gameLayer);
    addNormalLine(1);

    return true;
}
 void HelloWorld::addNormalLine(int lineIndex){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    GameBlock *b;
    int blackIndex = rand()%4;
    
    for (int i=0; i<4; i++) {
        b = GameBlock::createWithArgs(blackIndex==i?Color3B::BLACK:Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),"",20,Color4B::BLACK);
        gameLayer->addChild(b);
        
        b->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
        b->setLineIndex(lineIndex);
    }
    
    linesCount++;
}