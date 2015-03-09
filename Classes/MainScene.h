#ifndef __MAIN_SCENE_GAME_H__
#define __MAIN_SCENE_GAME_H__

#include "cocos2d.h" 

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	void menuMusicCallback(Ref* pSender);
	void menuPlayCallback(Ref* pSender);
	void menuNextCallback(Ref* pSender); 
	 
};
#endif
