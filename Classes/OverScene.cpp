#include "OverScene.h"
#include "MainScene.h"
#include "TDInvFileUtils.h"
#include "Constants.h"

bool OverScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int zorder = 1000;
	 
	auto btn_menu = MenuItemImage::create(
		"exit_0.png",
		"exit_1.png",
		CC_CALLBACK_1(OverScene::menuMenuCallback, this));
	btn_menu->setPosition(Point(visibleSize.width/2 + origin.x - 130, visibleSize.height/2 + origin.y-25));

	 
	auto menu = Menu::create(btn_menu ,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, zorder++); 
	
	int bast = Cocos2DxFileUtils::getIntegerDataFromSD(SD_BESTSCORE,0);
	 
		//Cocos2DxFileUtils::saveIntegerDataToSD(SD_BESTSCORE,);
	 

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

void OverScene::menuMenuCallback(Ref* pSender)
{
	log("pause scene popscene");
	//Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(MainScene::createScene());
	 
}

void OverScene::menuReplayCallback(Ref* pSender)
{
	 
	Director::getInstance()->popScene();
}

void OverScene::menuNextCallback(Ref* pSender)
{
 
	Director::getInstance()->popScene();
}

 