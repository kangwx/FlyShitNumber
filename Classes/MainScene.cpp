#include "MainScene.h"

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
	 
	 
	return true;
} 
 
 

void MainScene::menuMenuCallback(Ref* pSender)
{
	 
	 
}

void MainScene::menuReplayCallback(Ref* pSender)
{
	 
	Director::getInstance()->popScene();
}

void MainScene::menuNextCallback(Ref* pSender)
{
 
	Director::getInstance()->popScene();
}

 