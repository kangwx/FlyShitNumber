#include "PauseScene.h"
#include "MainScene.h"
#include "GameScene.h"

bool PauseScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int zorder = 1000;
	 

	auto label = LabelTTF::create();
	label->setString("Pauseing");
	label->setFontSize(100);
	label->setPosition(visibleSize.width/2,visibleSize.height/2+100);
	addChild(label);

	auto btn_menu = MenuItemImage::create(
		"exit_0.png",
		"exit_1.png",
		CC_CALLBACK_1(PauseScene::menuExitCallback, this));
	btn_menu->setPosition(Point(visibleSize.width/2 + origin.x - 130, visibleSize.height/2 + origin.y-25));
	
	
	MenuItemFont::setFontSize(50);
	auto exit_menu = MenuItemFont::create("Exit",CC_CALLBACK_1(PauseScene::menuExitCallback, this)); 
	exit_menu->setPosition(Point(visibleSize.width/2 + origin.x - 250, visibleSize.height/2  - 250));
	exit_menu->setColor(Color3B::BLACK);
	 
	auto restart_menu = MenuItemFont::create("Restart",CC_CALLBACK_1(PauseScene::menuReplayCallback, this)); 
	restart_menu->setPosition(Point(visibleSize.width/2 + origin.x  , visibleSize.height/2  - 250));
	restart_menu->setColor(Color3B::BLACK);

	auto continue_menu = MenuItemFont::create("Continue",CC_CALLBACK_1(PauseScene::menuNextCallback, this)); 
	continue_menu->setPosition(Point(visibleSize.width/2 + origin.x + 250, visibleSize.height/2  - 250));
	continue_menu->setColor(Color3B::BLACK);
	 
	auto menu = Menu::create(exit_menu,restart_menu,continue_menu ,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, zorder++); 
	return true;
} 
 
Scene* PauseScene::scene(RenderTexture* sqr,bool isFlip)
{             
	Scene *m_scene = Scene::create();  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	_spr->setPosition(Point(visibleSize.width/2, visibleSize.height/2));  
	_spr->setFlippedY(isFlip);  
	_spr->setColor(Color3B::GRAY);  
	m_scene->addChild(_spr);  
	PauseScene* layerr = PauseScene::create();
	layerr->setScale(0.1f);
	m_scene->addChild(layerr);
	layerr->runAction(ScaleTo::create(0.5f,1.0f));
	return m_scene;  
}

void PauseScene::menuExitCallback(Ref* pSender)
{
	log("pause scene popscene");
	//Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(MainScene::createScene());
	 
}

void PauseScene::menuReplayCallback(Ref* pSender)
{
	 
	GameScene::m_scoreNum = 2;
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void PauseScene::menuNextCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
  
	//GameScene::m_scoreNum = 2;
	//Director::getInstance()->replaceScene(GameScene::createScene());
}

 