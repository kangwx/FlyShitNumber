#include "OverScene.h"
#include "MainScene.h"
#include "TDInvFileUtils.h"
#include "Constants.h"
#include "GameScene.h"

bool OverScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int zorder = 1000;
	 
	
	auto label = LabelTTF::create();
	char c_title[100];
	sprintf(c_title,"Do you want to live? +%d",GameScene::m_reliveCount);
	 
	label->setString(c_title);
	label->setFontSize(50);
	label->setPosition(visibleSize.width/2,visibleSize.height/2+100);
	addChild(label);

	auto btn_menu = MenuItemImage::create(
		"exit_0.png",
		"exit_1.png",
		CC_CALLBACK_1(OverScene::menuExitCallback, this));
	btn_menu->setPosition(Point(visibleSize.width/2 + origin.x - 130, visibleSize.height/2 + origin.y-25));

	 MenuItemFont::setFontSize(50);
	auto exit_menu = MenuItemFont::create("Exit",CC_CALLBACK_1(OverScene::menuExitCallback, this)); 
	exit_menu->setPosition(Point(visibleSize.width/2 + origin.x - 250, visibleSize.height/2  - 250));
	exit_menu->setColor(Color3B::BLACK);
	 
	auto continue_menu = MenuItemFont::create("Continue",CC_CALLBACK_1(OverScene::menuNextCallback, this)); 
	continue_menu->setPosition(Point(visibleSize.width/2 + origin.x + 250, visibleSize.height/2  - 250));

	continue_menu->setColor(GameScene::m_reliveCount>0?Color3B::BLACK:Color3B::GRAY);

	auto menu = Menu::create(exit_menu,continue_menu ,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, zorder++); 
	
	int best = Cocos2DxFileUtils::getIntegerDataFromSD(SD_BESTSCORE,0);
	if( GameScene::m_bestScore > best ){
		Cocos2DxFileUtils::saveIntegerDataToSD(SD_BESTSCORE,GameScene::m_bestScore);
	}
	 

	return true;
} 
 
Scene* OverScene::scene(RenderTexture* sqr,bool isFlip)
{
	Scene *m_scene = Scene::create();  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
	_spr->setPosition(Point(visibleSize.width/2, visibleSize.height/2));  
	_spr->setFlippedY(isFlip);  
	_spr->setColor(Color3B::GRAY);  
	m_scene->addChild(_spr);  
	OverScene* layerr = OverScene::create();
	layerr->setScale(0.1f);
	m_scene->addChild(layerr);
	layerr->runAction(ScaleTo::create(0.5f,1.0f));
	return m_scene;  
}

void OverScene::menuExitCallback(Ref* pSender)
{
	log("pause scene popscene");
	//Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(MainScene::createScene());
	 
}

void OverScene::menuReplayCallback(Ref* pSender)
{
	  
	GameScene::m_scoreNum = 2;
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void OverScene::menuNextCallback(Ref* pSender)
{
	if(GameScene::m_reliveCount>0){
		//Director::getInstance()->popScene();
		Director::getInstance()->replaceScene(GameScene::createScene());
		GameScene::m_reliveCount--;
		Cocos2DxFileUtils::saveIntegerDataToSD(SD_RELIVECOUNT,GameScene::m_reliveCount); 
	}
}

 