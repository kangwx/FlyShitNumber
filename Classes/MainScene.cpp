#include "MainScene.h"
#include "GameScene.h"

USING_NS_CC;

bool MainScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int zorder = 1000;
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fly.plist", "fly.png");
	

	auto bg = Sprite::create("bg.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
	auto logo = Sprite::create("logo.png");
    logo->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + 100));
    this->addChild(logo);
	 
	auto btn_menu = MenuItemImage::create(
		"btn_start.png",
		"btn_start.png",
		CC_CALLBACK_1(MainScene::menuPlayCallback, this));
	btn_menu->setPosition(Point(visibleSize.width/2 + 250  , visibleSize.height/2 - 400 ));

	 auto btn_music = MenuItemImage::create(
		"btn_music.png",
		"btn_music.png",
		CC_CALLBACK_1(MainScene::menuMusicCallback, this));
	btn_music->setPosition(Point(visibleSize.width/2 - 300  , visibleSize.height/2 - 500 ));

	auto menu = Menu::create(btn_menu,btn_music ,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, zorder++); 

	return true;
} 

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	//auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
  
void MainScene::menuMusicCallback(Ref* pSender)
{
	   
}

void MainScene::menuPlayCallback(Ref* pSender)
{
	GameScene::m_scoreNum = 2;
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void MainScene::menuNextCallback(Ref* pSender)
{
 
	Director::getInstance()->popScene();
}

 